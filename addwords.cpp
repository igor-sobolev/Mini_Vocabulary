#include "addwords.h"
#include "ui_addwords.h"
#include <QMessageBox>
#include <QtSql/qsqlquery.h>

AddWords::AddWords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWords)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

AddWords::~AddWords()
{
    delete ui;
}

void AddWords::on_pushButtonClose_clicked()
{
    QDialog::close();
}

void AddWords::on_pushButtonAdd_clicked()
{
    if(ui->lineEditWord->text()==""){
        QMessageBox::warning(this,"Warning","Enter word!");
        return;
    }
    if(ui->lineEditTranslation->text()==""){
        QMessageBox::warning(this,"Warning","Enter translation!");
        return;
    }
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO words (word, translation, note)"
                                  "VALUES (:word, :translation, :note);");
    addQuery.bindValue(":word", ui->lineEditWord->text());
    addQuery.bindValue(":translation", ui->lineEditTranslation->text());
    addQuery.bindValue(":note", ui->lineEditNote->text());
    if(addQuery.exec()){
        QMessageBox::information(this,"Notification","Done!");
    }
    else QMessageBox::critical(this,"Error","Bad query!");
    ui->lineEditNote->setText("");
    ui->lineEditWord->setText("");
    ui->lineEditTranslation->setText("");
}
