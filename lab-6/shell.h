#ifndef SHELL_H
#define SHELL_H

#include <QJsonObject>
#include <QString>
#include <QList>

struct Shell
{
    QString name;
    QString description;
    int currentDurability = 0;
    int initialDurability = 0;
    QString rarity;
    double price = 0.0;

    QJsonObject toJson() const;
    static bool fromJson(const QJsonObject &object, Shell &shell, QString &error);

    bool isBroken(QString *reason = nullptr) const;
};

#endif