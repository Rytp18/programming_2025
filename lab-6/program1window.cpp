#include "program1window.h"
#include "ui_program1.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>

Program1Window::Program1Window(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Program1Window)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked,
            this, &Program1Window::saveObject);

    connect(ui->txtButton, &QPushButton::clicked,
            this, &Program1Window::importFromTxt);

    connect(ui->clearButton, &QPushButton::clicked,
            this, &Program1Window::clearForm);

    ui->currentDurabilitySpin->setRange(0, 1000000000);
    ui->initialDurabilitySpin->setRange(0, 1000000000);

    ui->priceSpin->setRange(0.0, 1000000000000.0);
    ui->priceSpin->setDecimals(2);

    connect(ui->currentDurabilitySpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &Program1Window::currentDurabilityChanged);

    connect(ui->initialDurabilitySpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &Program1Window::initialDurabilityChanged);

    ui->currentDurabilitySpin->setMaximum(
        ui->initialDurabilitySpin->value()
        );

    ui->initialDurabilitySpin->setMinimum(
        ui->currentDurabilitySpin->value()
        );
}

Program1Window::~Program1Window()
{
    delete ui;
}

bool Program1Window::validateDurability(QString &error) const
{
    const int current =
        ui->currentDurabilitySpin->value();

    const int initial =
        ui->initialDurabilitySpin->value();

    if (initial < current)
    {
        error =
            "Начальная прочность не может быть меньше текущей.\n\n"
            "Текущая прочность: " +
            QString::number(current) +
            "\nНачальная прочность: " +
            QString::number(initial);

        return false;
    }

    return true;
}

void Program1Window::currentDurabilityChanged(int value)
{
    ui->initialDurabilitySpin->setMinimum(value);

    if (ui->initialDurabilitySpin->value() < value)
    {
        ui->initialDurabilitySpin->setValue(value);
    }
}

void Program1Window::initialDurabilityChanged(int value)
{
    ui->currentDurabilitySpin->setMaximum(value);

    if (ui->currentDurabilitySpin->value() > value)
    {
        ui->currentDurabilitySpin->setValue(value);
    }
}

Shell Program1Window::readForm(QString &error) const
{
    Shell shell;

    shell.name =
        ui->nameEdit->text().trimmed();

    shell.description =
        ui->descriptionEdit->toPlainText().trimmed();

    shell.currentDurability =
        ui->currentDurabilitySpin->value();

    shell.initialDurability =
        ui->initialDurabilitySpin->value();

    shell.rarity =
        ui->rarityEdit->text().trimmed();

    shell.price =
        ui->priceSpin->value();

    if (shell.name.isEmpty())
    {
        error = "Заполните поле «Название».";
        return {};
    }

    if (shell.description.isEmpty())
    {
        error = "Заполните поле «Описание».";
        return {};
    }

    if (shell.rarity.isEmpty())
    {
        error = "Заполните поле «Редкость».";
        return {};
    }

    if (!validateDurability(error))
    {
        return {};
    }

    return shell;
}

bool Program1Window::appendToJsonFile(
    const QString &fileName,
    const Shell &shell,
    QString &error)
{
    QJsonArray objects;

    QFile file(fileName);

    if (file.exists())
    {
        if (!file.open(
                QIODevice::ReadOnly |
                QIODevice::Text))
        {
            error =
                "Не удалось открыть существующий JSON для чтения.";

            return false;
        }

        const QByteArray data =
            file.readAll();

        file.close();

        if (!data.trimmed().isEmpty())
        {
            QJsonParseError parseError;

            const QJsonDocument document =
                QJsonDocument::fromJson(
                    data,
                    &parseError
                    );
            if (parseError.error !=
                    QJsonParseError::NoError ||
                !document.isArray())
            {
                error =
                    "JSON должен содержать массив объектов.\n"
                    "Файл повреждён или имеет неверный формат.";

                return false;
            }

            objects =
                document.array();
        }
    }

    objects.append(shell.toJson());

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Text |
            QIODevice::Truncate))
    {
        error =
            "Не удалось открыть JSON для записи.";

        return false;
    }

    file.write(
        QJsonDocument(objects)
            .toJson(QJsonDocument::Indented)
        );

    file.close();

    return true;
}

void Program1Window::saveObject()
{
    QString error;

    const Shell shell =
        readForm(error);

    if (!error.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Ошибка",
            error
            );

        return;
    }

    const QString fileName =
        QFileDialog::getSaveFileName(
            this,
            "Создать новый JSON или выбрать существующий",
            QString(),
            "JSON (*.json)"
            );

    if (fileName.isEmpty())
        return;

    QString finalName = fileName;

    if (!finalName.endsWith(
            ".json",
            Qt::CaseInsensitive))
    {
        finalName += ".json";
    }

    if (!appendToJsonFile(
            finalName,
            shell,
            error))
    {
        QMessageBox::critical(
            this,
            "Ошибка записи",
            error
            );

        return;
    }

    QString note =
        "Объект успешно добавлен в конец файла:\n\n" +
        finalName;

    if (shell.currentDurability <
        shell.initialDurability)
    {
        note +=
            "\n\nВнимание!\n"
            "Объект считается БИТЫМ,\n"
            "так как текущая прочность ниже начальной.";
    }

    QMessageBox::information(
        this,
        "Готово",
        note
        );
}

bool Program1Window::parseTxtFile(
    const QString &fileName,
    Shell &shell,
    QString &error) const
{
    QFile file(fileName);

    if (!file.open(
            QIODevice::ReadOnly |
            QIODevice::Text))
    {
        error =
            "Не удалось открыть TXT-файл.";

        return false;
    }

    QTextStream in(&file);

    QStringList lines;

    while (!in.atEnd())
    {
        const QString line =
            in.readLine().trimmed();

        if (!line.isEmpty())
        {
            lines << line;
        }
    }

    file.close();

    if (lines.size() < 6)
    {
        error =
            "TXT должен содержать 6 полей объекта.";

        return false;
    }

    QString name;
    QString description;
    QString rarity;

    QString currentText;
    QString initialText;
    QString priceText;

    bool namedFormat = false;

    for (const QString &line : lines)
    {
        const int colon =
            line.indexOf(':');

        if (colon > 0)
        {
            namedFormat = true;

            const QString key =
                line.left(colon)
                    .trimmed()
                    .toLower();

            const QString value =
                line.mid(colon + 1)
                    .trimmed();

            if (key == "название" ||
                key == "name")
            {
                name = value;
            }
            else if (key == "описание" ||
                     key == "description")
            {
                description = value;
            }
            else if (key == "текущая прочность" ||
                     key == "current durability")
            {
                currentText = value;
            }
            else if (key == "начальная прочность" ||
                     key == "initial durability")
            {
                initialText = value;
            }
            else if (key == "редкость" ||
                     key == "rarity")
            {
            rarity = value;
            }
            else if (key == "цена" ||
                     key == "price")
            {
                priceText = value;
            }
        }
    }

    if (!namedFormat)
    {
        name =
            lines.at(0);

        description =
            lines.at(1);

        currentText =
            lines.at(2);

        initialText =
            lines.at(3);

        rarity =
            lines.at(4);

        priceText =
            lines.at(5);
    }

    bool okCurrent = false;
    bool okInitial = false;
    bool okPrice = false;

    const int current =
        currentText.toInt(&okCurrent);

    const int initial =
        initialText.toInt(&okInitial);

    QString normalizedPrice =
        priceText;

    normalizedPrice.replace(
        ',',
        '.'
        );

    const double price =
        normalizedPrice.toDouble(
            &okPrice
            );

    if (name.isEmpty() ||
        description.isEmpty() ||
        rarity.isEmpty())
    {
        error =
            "В TXT не заполнено одно из текстовых полей.";

        return false;
    }

    if (!okCurrent ||
        current < 0)
    {
        error =
            "Текущая прочность в TXT должна быть "
            "целым числом >= 0.";

        return false;
    }

    if (!okInitial ||
        initial < 0)
    {
        error =
            "Начальная прочность в TXT должна быть "
            "целым числом >= 0.";

        return false;
    }

    if (!okPrice ||
        price < 0)
    {
        error =
            "Цена в TXT должна быть числом >= 0.";

        return false;
    }

    if (initial < current)
    {
        error =
            "Ошибка в TXT!\n\n"
            "Начальная прочность не может быть "
            "меньше текущей.\n\n"
            "Текущая прочность: " +
            QString::number(current) +
            "\nНачальная прочность: " +
            QString::number(initial);

        return false;
    }

    shell.name =
        name;

    shell.description =
        description;

    shell.currentDurability =
        current;

    shell.initialDurability =
        initial;

    shell.rarity =
        rarity;

    shell.price =
        price;

    return true;
}

void Program1Window::importFromTxt()
{
    const QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Выберите TXT-файл",
            QString(),
            "Текстовые файлы (*.txt);;Все файлы (*.*)"
            );

    if (fileName.isEmpty())
        return;

    Shell shell;
    QString error;

    if (!parseTxtFile(
            fileName,
            shell,
            error))
    {
        QMessageBox::warning(
            this,
            "Ошибка TXT",
            error
            );

        return;
    }

    ui->nameEdit->setText(
        shell.name
        );

    ui->descriptionEdit->setPlainText(
        shell.description
        );

    ui->currentDurabilitySpin->setValue(
        shell.currentDurability
        );

    ui->initialDurabilitySpin->setValue(
        shell.initialDurability
        );

    ui->rarityEdit->setText(
        shell.rarity
        );

    ui->priceSpin->setValue(
        shell.price
        );

    QString message =
        "Данные из TXT перенесены в форму.\n"
        "Теперь их можно отредактировать "
        "и сохранить в JSON.";

    if (shell.currentDurability <
        shell.initialDurability)
    {
        message +=
            "\n\nВнимание!\n"
            "Объект будет считаться БИТЫМ,\n"
            "так как текущая прочность ниже начальной.";
    }

    QMessageBox::information(
        this,
        "TXT загружен",
        message
        );
}

void Program1Window::clearForm()
{
    ui->nameEdit->clear();

    ui->descriptionEdit->clear();

    ui->currentDurabilitySpin->setValue(
        100
        );

    ui->initialDurabilitySpin->setValue(
        100
        );

    ui->rarityEdit->clear();

    ui->priceSpin->setValue(
        0
        );

    ui->nameEdit->setFocus();
}