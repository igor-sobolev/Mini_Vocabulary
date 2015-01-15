#include "testdialog.h"
#include "ui_testdialog.h"
#include "test.h"

TestDialog::TestDialog(QWidget *parent, bool snd) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    sounds = snd;
    this->parent = parent;
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::on_pushButton_2_clicked()
{
    QDialog::close();
}

void TestDialog::on_pushButton_clicked()
{
    int selection = 0;
    if(ui->radioButtonOften->isChecked()) selection = 1;
    if(ui->radioButtonRandom->isChecked()) selection = 2;
    int count = ui->spinBoxNumber->value();
    Test *t = new Test(parent,count,sounds,selection);
    t->show();
    QDialog::close();
}
