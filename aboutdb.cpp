#include "aboutdb.h"
#include "ui_aboutdb.h"
#include <QtSql/qsqlquery.h>
#include <QMessageBox>

AboutDB::AboutDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDB)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    int records=0, notes=0;
    QSqlQuery qry;
    if (qry.exec("SELECT note FROM words"))
    {
        while (qry.next()) {
            QString note = qry.value(0).toString();
            records++;
            if(note!="")notes++;
        }
        ui->label->setText("<html><head/><body><p align=\"center\"span style=\" font-size:10pt;\">SQLite datbase. Managed by SQLite Managerversion 3.2</span></p><p align=\"center\"><span style=\" font-size:10pt;\"><br/></span></p><p align=\"center\"><span style=\" font-size:10pt;\">Database contains "+QString("%1").arg(records)+" records and "+QString("%1").arg(notes)+" of them are noted.</span></p></body></html>");
    }
    else {
        QMessageBox::critical(this, "Error","Wrong query");
    }
}

AboutDB::~AboutDB()
{
    delete ui;
}

void AboutDB::on_pushButton_clicked()
{
    QDialog::close();
}
