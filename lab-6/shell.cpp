#include "shell.h"

#include <QJsonValue>
#include <QtMath>

QJsonObject Shell::toJson() const
{
    QJsonObject object;
    object["название"] = name;
    object["описание"] = description;
    object["текущая прочность"] = currentDurability;
    object["начальная прочность"] = initialDurability;
    object["редкость"] = rarity;
    object["цена"] = price;
    return object;
}

bool Shell::fromJson(const QJsonObject &object, Shell &shell, QString &error)
{
    const QStringList required = {
        "название", "описание", "текущая прочность",
        "начальная прочность", "редкость", "цена"
    };

    for (const QString &key : required) {
        if (!object.contains(key)) {
            error = QString("Нет поля «%1».").arg(key);
            return false;
        }
    }

    if (!object["название"].isString() || object["название"].toString().trimmed().isEmpty()) {
        error = "Поле «название» должно быть непустой строкой.";
        return false;
    }

    if (!object["описание"].isString() || object["описание"].toString().trimmed().isEmpty()) {
        error = "Поле «описание» должно быть непустой строкой.";
        return false;
    }

    if (!object["редкость"].isString() || object["редкость"].toString().trimmed().isEmpty()) {
        error = "Поле «редкость» должно быть непустой строкой.";
        return false;
    }

    const QJsonValue current = object["текущая прочность"];
    const QJsonValue initial = object["начальная прочность"];
    const QJsonValue price = object["цена"];

    if (!current.isDouble() || current.toDouble() < 0 || current.toDouble() != qFloor(current.toDouble())) {
        error = "Поле «текущая прочность» должно быть целым числом >= 0.";
        return false;
    }

    if (!initial.isDouble() || initial.toDouble() <= 0 || initial.toDouble() != qFloor(initial.toDouble())) {
        error = "Поле «начальная прочность» должно быть целым числом > 0.";
        return false;
    }

    if (!price.isDouble() || price.toDouble() < 0) {
        error = "Поле «цена» должна быть числом >= 0.";
        return false;
    }

    shell.name = object["название"].toString().trimmed();
    shell.description = object["описание"].toString().trimmed();
    shell.currentDurability = current.toInt();
    shell.initialDurability = initial.toInt();
    shell.rarity = object["редкость"].toString().trimmed();
    shell.price = price.toDouble();

    return true;
}

bool Shell::isBroken(QString *reason) const
{
    if (name.trimmed().isEmpty()) {
        if (reason) *reason = "Не заполнено название.";
        return true;
    }

    if (description.trimmed().isEmpty()) {
        if (reason) *reason = "Не заполнено описание.";
        return true;
    }

    if (rarity.trimmed().isEmpty()) {
        if (reason) *reason = "Не заполнена редкость.";
        return true;
    }

    if (initialDurability <= 0) {
        if (reason) *reason = "Начальная прочность должна быть > 0.";
        return true;
    }

    if (currentDurability < 0) {
        if (reason) *reason = "Текущая прочность не может быть отрицательной.";
        return true;
    }

    if (price < 0) {
        if (reason) *reason = "Цена не может быть отрицательной.";
        return true;
    }

    if (currentDurability < initialDurability) {
        if (reason) *reason = "Текущая прочность ниже начальной.";
        return true;
    }

    if (currentDurability > initialDurability) {
        if (reason) *reason = "Текущая прочность выше начальной.";
        return true;
    }

    return false;
}