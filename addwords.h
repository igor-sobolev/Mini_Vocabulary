#ifndef ADDWORDS_H
#define ADDWORDS_H

#include <QDialog>

namespace Ui {
class AddWords;
}

class AddWords : public QDialog
{
    Q_OBJECT

public:
    explicit AddWords(QWidget *parent = 0);
    ~AddWords();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonAdd_clicked();

private:
    Ui::AddWords *ui;
};

#endif // ADDWORDS_H
