#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void printTranslation(QString);

private slots:
    void on_actionAdd_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionAbout_program_triggered();

    void on_actionExit_triggered();

    void on_actionDelete_triggered();

    void on_actionStart_triggered();

    void on_actionSettings_triggered();

    void on_actionDelete_all_triggered();

    void on_actionAbout_database_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase myDB;
    bool sounds;
    Settings *settingsWindow;
};

#endif // MAINWINDOW_H
