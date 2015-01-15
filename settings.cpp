#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    QDialog::hide();
}
bool Settings::checkSounds(){
    return ui->checkBoxSounds->isChecked();
}
