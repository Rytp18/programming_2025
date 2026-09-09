#include "program2window.h"
#include "ui_program2.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <algorithm>

Program2Window::Program2Window(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Program2Window)
{
    ui->setupUi(this);

    connect(ui->loadButton, &QPushButton::clicked,
            this, &Program2Window::loadJson);

    ui->correctTable->setSortingEnabled(false);
    ui->brokenTable->setSortingEnabled(false);

    ui->correctTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->brokenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->correctTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->brokenTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->correctTable->verticalHeader()->setVisible(false);
    ui->brokenTable->verticalHeader()->setVisible(false);
}

Program2Window::~Program2Window()
{
    delete ui;
}

bool Program2Window::readJson(const QString &fileName,
                              QList<Shell> &valid,
                              QList<QJsonObject> &broken,
                              QString &error) const
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = "Не удалось открыть JSON-файл.";
        return false;
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        error = "Ошибка разбора JSON: " + parseError.errorString();
        return false;
    }

    if (!document.isArray()) {
        error = "Корневой элемент JSON должен быть массивом объектов.";
        return false;
    }

    const QJsonArray array = document.array();

    for (const QJsonValue &value : array) {
        if (!value.isObject()) {
            QJsonObject bad;
            bad["ошибка"] = "Элемент массива не является объектом.";
            broken.append(bad);
            continue;
        }

        const QJsonObject object = value.toObject();
        Shell shell;
        QString objectError;

        if (!Shell::fromJson(object, shell, objectError)) {
            QJsonObject bad = object;
            bad["ошибка"] = objectError;
            broken.append(bad);
            continue;
        }

        QString reason;
        if (shell.isBroken(&reason)) {
            QJsonObject bad = object;
            bad["ошибка"] = reason;
            broken.append(bad);
        } else {
            valid.append(shell);
        }
    }

    std::sort(valid.begin(), valid.end(),
              [](const Shell &a, const Shell &b) {
                  return QString::localeAwareCompare(a.name, b.name) > 0;
              });

    return true;
}

void Program2Window::fillTable(QTableWidget *table,
                               const QList<Shell> &objects,
                               bool broken)
{
    table->clearContents();

    if (broken) {
        table->setRowCount(objects.size());

        for (int row = 0; row < objects.size(); ++row) {
            const Shell &s = objects.at(row);

            table->setItem(row, 0, new QTableWidgetItem(s.name));
            table->setItem(row, 1, new QTableWidgetItem(s.description));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(s.currentDurability)));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(s.initialDurability)));
            table->setItem(row, 4, new QTableWidgetItem(s.rarity));
            table->setItem(row, 5, new QTableWidgetItem(QString::number(s.price, 'f', 2)));
        }
    } else {
        table->setRowCount(objects.size());

        for (int row = 0; row < objects.size(); ++row) {
            const Shell &s = objects.at(row);

            table->setItem(row, 0, new QTableWidgetItem(s.name));
            table->setItem(row, 1, new QTableWidgetItem(s.description));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(s.currentDurability)));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(s.initialDurability)));
            table->setItem(row, 4, new QTableWidgetItem(s.rarity));
            table->setItem(row, 5, new QTableWidgetItem(QString::number(s.price, 'f', 2)));
        }
    }
}

void Program2Window::saveBrokenJson(const QString &sourceFile,
                                    const QList<QJsonObject> &broken)
{
    if (broken.isEmpty())
        return;

    const QFileInfo info(sourceFile);
    const QString brokenFile =
        info.absolutePath() + "/" + info.completeBaseName() + "_broken.json";

    QJsonArray array;
    for (const QJsonObject &object : broken)
        array.append(object);

    QFile file(brokenFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
        ui->fileLabel->setText(
            QString("Источник: %1\nБитые сохранены: %2")
                .arg(info.fileName(), QFileInfo(brokenFile).fileName()));
    }
}

void Program2Window::loadJson()
{
    const QString fileName = QFileDialog::getOpenFileName(
        this,
        "Выберите исходный JSON",
        QString(),
        "JSON (*.json)");

    if (fileName.isEmpty())
        return;

    QList<Shell> valid;
    QList<QJsonObject> broken;
    QString error;

    if (!readJson(fileName, valid, broken, error)) {
        QMessageBox::critical(this, "Ошибка JSON", error);
        return;
    }

    QList<Shell> brokenForTable;

    for (const QJsonObject &object : broken) {
        Shell s;
        s.name = object.value("название").toString();
        s.description = object.value("описание").toString();
        s.currentDurability = object.value("текущая прочность").toInt();
        s.initialDurability = object.value("начальная прочность").toInt();
        s.rarity = object.value("редкость").toString();
        s.price = object.value("цена").toDouble();
        brokenForTable.append(s);
    }

    fillTable(ui->correctTable, valid, false);
    fillTable(ui->brokenTable, brokenForTable, true);

    ui->correctCountLabel->setText(
        QString("Корректные: %1").arg(valid.size()));
    ui->brokenCountLabel->setText(
        QString("Ошибки: %1").arg(broken.size()));

    ui->fileLabel->setText(
        QString("Источник: %1").arg(QFileInfo(fileName).fileName()));

    saveBrokenJson(fileName, broken);

    QString message = QString("Загрузка завершена.\n\nКорректных объектов: %1\nБитых объектов: %2")
                          .arg(valid.size())
                          .arg(broken.size());

    if (!broken.isEmpty()) {
        const QFileInfo info(fileName);
        const QString brokenName =
            info.completeBaseName() + "_broken.json";
        message += "\n\nБитые объекты сохранены в: " + brokenName;
    }

    QMessageBox::information(this, "Готово", message);
}