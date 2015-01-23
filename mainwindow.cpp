#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include "addwords.h"
#include "about.h"
#include "delete.h"
#include "testdialog.h"
#include "aboutdb.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    settingsWindow = new Settings();
    myDB = QSqlDatabase::addDatabase("QSQLITE");

    QString pathToDB = QDir::currentPath()+QString("/words.sqlite");
    myDB.setDatabaseName(pathToDB);

    QFileInfo checkFile(pathToDB);

    if (checkFile.isFile()) {
        if (!myDB.open()) {
            QMessageBox::critical(this, "Error", "Database File was not opened");
        }
        else{
            ui->actionAdd->setEnabled(true);
            ui->actionDelete->setEnabled(true);
            ui->actionDelete_all->setEnabled(true);
            ui->actionStart->setEnabled(true);
            ui->actionAbout_database->setEnabled(true);
        }
    }
    else {
        QMessageBox::critical(this, "Error","Database File does not exist");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    myDB.close();
}

void MainWindow::printTranslation(QString s){
    ui->textEdit->setText("");
    if(s == "")return;
    QSqlQuery qry;

    if (qry.exec("SELECT word, translation, note FROM words WHERE word LIKE \'" + ui->lineEdit->text() +
                 "%\'"))
    {
        while (qry.next()) {
            QString word = qry.value(0).toString();
            QString translation = qry.value(1).toString();
            QString note = qry.value(2).toString();
            ui->textEdit->textCursor().insertText(word+" - "+translation+"\n"+note+"\n\n");
        }
    }
    else {
        QMessageBox::critical(this, "Error","Wrong query");
    }

    if (qry.exec("SELECT word, translation, note FROM words WHERE word LIKE \'to " + ui->lineEdit->text() +
                 "%\'"))
    {
        while (qry.next()) {
            QString word = qry.value(0).toString();
            QString translation = qry.value(1).toString();
            QString note = qry.value(2).toString();
            ui->textEdit->textCursor().insertText(word+" - "+translation+"\n"+note+"\n\n");
        }
    }
    else {
        QMessageBox::critical(this, "Error","Wrong query");
    }
}

void MainWindow::on_actionAdd_triggered()
{
    AddWords *w = new AddWords();
    w->show();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionAbout_program_triggered()
{
    About *a = new About();
    a->show();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionDelete_triggered()
{
    Delete *d = new Delete();
    d->show();
}

void MainWindow::on_actionStart_triggered()
{
    TestDialog *d;
    if(settingsWindow->checkSounds()){
        d=new TestDialog(this,1);
    }
    else{
        d=new TestDialog(this,0);
    }
    d->show();
}

void MainWindow::on_actionSettings_triggered()
{
    settingsWindow->show();
}

void MainWindow::on_actionDelete_all_triggered()
{
    QMessageBox::StandardButton decision = QMessageBox::warning(this,"Warning","Do you really want to delete all words?",QMessageBox::Yes|QMessageBox::No);
    if(decision==QMessageBox::Yes){
        QSqlQuery deleteAllQuery;
        deleteAllQuery.prepare("DELETE FROM words");
        if(deleteAllQuery.exec()){
            QMessageBox::information(this,"Notification","Done!");
        }
        else QMessageBox::critical(this,"Error","Bad query!");
    }
}

void MainWindow::on_actionAbout_database_triggered()
{
    AboutDB *adb = new AboutDB();
    adb->show();
}
