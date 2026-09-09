#ifndef PROGRAM1WINDOW_H
#define PROGRAM1WINDOW_H

#include <QMainWindow>

#include "shell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Program1Window; }
QT_END_NAMESPACE

class Program1Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Program1Window(QWidget *parent = nullptr);
    ~Program1Window();

private slots:
    void saveObject();
    void importFromTxt();
    void clearForm();
    void currentDurabilityChanged(int value);
    void initialDurabilityChanged(int value);

private:
    Ui::Program1Window *ui;

    Shell readForm(QString &error) const;
    bool appendToJsonFile(const QString &fileName, const Shell &shell, QString &error);
    bool parseTxtFile(const QString &fileName, Shell &shell, QString &error) const;
    bool validateDurability(QString &error) const;
};

#endif