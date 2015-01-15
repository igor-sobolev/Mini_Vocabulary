#include "test.h"
#include "ui_test.h"
#include <QtSql/qsqlquery.h>
#include <QMessageBox>
#include <QList>
#include <stdlib.h>
#include <time.h>
#include <QSound>
#include <QDebug>

Test::Test(QWidget *parent,int cnt, bool snd, int slc) :
    QDialog(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    progress = 1;
    count = cnt;
    sounds = snd;
    selection = slc;
    correct=0;
    selectedList = new QStack<SelectedWord>();
    casing(selection);
    current = selectedList->pop();
    ui->labelProgress->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Progress: "+QString("%1").arg(progress)+"/"+QString("%1").arg(count)+"</span></p></body></html>");
    ui->labelCorrect->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Correct: "+QString("%1").arg(correct)+"/"+QString("%1").arg(count)+"</span></p></body></html>");
    ui->lineEditWord->setText(current.word);
    ui->pushButtonAccept->setEnabled(true);
    ui->pushButtonEnd->setEnabled(true);
    ui->pushButtonNext->setEnabled(true);
}

Test::~Test()
{
    delete ui;
}

void Test::casing(int selection){
    QSqlQuery qry;
    switch(selection){
    case 0:
        if (qry.exec("SELECT word, translation, test_done FROM words"))
        {
            QList<SelectedWord> list;
            while (qry.next()) {
                SelectedWord sw;
                sw.word = qry.value(0).toString();
                sw.translation = qry.value(01).toString();
                sw.done = qry.value(2).toInt();
                list.append(sw);
            }
            if(count > list.length()) count = list.length();
            for(int k = 0; k < count; k++){
                int index = 0;
                int min = list.at(0).done;
                for(int i = 0; i < list.length(); i++){
                    if(min > list.at(i).done){
                        min = list.at(i).done;
                        index = i;
                    }
                }
                selectedList->append(list.at(index));
                list.removeAt(index);
            }
        }
        else {
            QMessageBox::critical(this, "Error","Wrong query");
        }
    break;
    case 1:
        if (qry.exec("SELECT word, translation, test_done FROM words"))
        {
            QList<SelectedWord> list;
            while (qry.next()) {
                SelectedWord sw;
                sw.word = qry.value(0).toString();
                sw.translation = qry.value(1).toString();
                sw.done = qry.value(2).toInt();
                list.append(sw);
            }
            if(count > list.length()) count = list.length();
            for(int k = 0; k < count; k++){
                int index = 0;
                int max = list.at(0).done;
                for(int i = 0; i < list.length(); i++){
                    if(max < list.at(i).done){
                        max = list.at(i).done;
                        index = i;
                    }
                }
                selectedList->append(list.at(index));
                list.removeAt(index);
            }
        }
        else {
            QMessageBox::critical(this, "Error","Wrong query");
        }
    break;
    case 2:
        srand(time(0));
        if (qry.exec("SELECT word, translation, test_done FROM words"))
        {
            QList<SelectedWord> list;
            while (qry.next()) {
                SelectedWord sw;
                sw.word = qry.value(0).toString();
                sw.translation = qry.value(1).toString();
                sw.done = qry.value(2).toInt();
                list.append(sw);
            }
            if(count > list.length()) count = list.length();
            for(int k = 0; k < count; k++){
                int index = 0;
                for(int i = 0; i < list.length(); i++){
                    double r=((double)(rand()%100))/100;
                    if(r>0.5){
                        index=i;
                    }
                }
                selectedList->append(list.at(index));
                list.removeAt(index);
            }
        }
        else {
            QMessageBox::critical(this, "Error","Wrong query");
        }
    break;
    }
}

void Test::on_pushButtonAccept_clicked()
{
    if(ui->lineEditTranslation->text().toLower()==current.translation.toLower()){
        if(sounds){
            QSound::play("sounds/High.wav");
        }
        correct++;
        ui->labelCorrect->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Correct: "+QString("%1").arg(correct)+"/"+QString("%1").arg(count)+"</span></p></body></html>");
        ui->lineEditTranslation->setStyleSheet("background : green;");
        current.done++;
        QSqlQuery updQuery;
        if(!updQuery.exec("UPDATE words SET test_done="+QString("%1").arg(current.done)+" WHERE word='"+current.word+"' AND translation='"+current.translation+"'"))
        {
            QMessageBox::critical(this,"Error","Bad query!");
        }
    }
    else{
        if(sounds){
            QSound::play("sounds/Grumble.wav");
        }
        ui->lineEditTranslation->setStyleSheet("background : red;");
    }
    ui->pushButtonAccept->setEnabled(false);
}

void Test::on_pushButtonNext_clicked()
{
    progress++;
    ui->labelProgress->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Progress: "+QString("%1").arg(progress)+"/"+QString("%1").arg(count)+"</span></p></body></html>");
    if(progress==count)ui->pushButtonNext->setEnabled(false);
    ui->pushButtonAccept->setEnabled(true);
    current = selectedList->pop();
    ui->lineEditWord->setText(current.word);
    ui->lineEditTranslation->setText("");
    ui->lineEditTranslation->setStyleSheet("background : white;");
}

void Test::on_pushButtonEnd_clicked()
{
    QDialog::close();
}
