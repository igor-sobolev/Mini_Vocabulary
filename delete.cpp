#include "delete.h"
#include "ui_delete.h"
#include <QtSql/qsqlquery.h>
#include <QMessageBox>

Delete::Delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Delete::~Delete()
{
    delete ui;
}

void Delete::on_pushButtonClose_clicked()
{
    QDialog::close();
}

void Delete::on_pushButtonDelete_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::warning(this,"Warning","Enter word!");
        return;
    }
    QSqlQuery addQuery;
    addQuery.prepare("DELETE FROM words WHERE word=\'"+ui->lineEdit->text()+"\'");
    if(addQuery.exec()){
        QMessageBox::information(this,"Notification","Done!");
    }
    else QMessageBox::critical(this,"Error","Bad query!");
    ui->lineEdit->setText("");
}
