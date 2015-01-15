#ifndef ABOUTDB_H
#define ABOUTDB_H

#include <QDialog>

namespace Ui {
class AboutDB;
}

class AboutDB : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDB(QWidget *parent = 0);
    ~AboutDB();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AboutDB *ui;
};

#endif // ABOUTDB_H
