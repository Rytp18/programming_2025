#ifndef PROGRAM2WINDOW_H
#define PROGRAM2WINDOW_H

#include <QMainWindow>
#include <QList>

#include "shell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Program2Window; }
QT_END_NAMESPACE

class Program2Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Program2Window(QWidget *parent = nullptr);
    ~Program2Window();

private slots:
    void loadJson();

private:
    Ui::Program2Window *ui;

    void fillTable(class QTableWidget *table,
                   const QList<Shell> &objects,
                   bool broken);
    bool readJson(const QString &fileName,
                  QList<Shell> &valid,
                  QList<QJsonObject> &broken,
                  QString &error) const;
    void saveBrokenJson(const QString &sourceFile,
                        const QList<QJsonObject> &broken);
};

#endif