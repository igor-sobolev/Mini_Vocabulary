#ifndef TEST_H
#define TEST_H

#include <QDialog>
#include "selectedword.h"
#include <QStack>

namespace Ui {
class Test;
}

class Test : public QDialog
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0, int cnt=10, bool sounds=1, int selection=0);
    ~Test();

private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonEnd_clicked();

private:
    Ui::Test *ui;
    int progress;
    int count;
    int correct;
    bool sounds;
    int selection;
    QStack<SelectedWord> *selectedList;
    SelectedWord current;
    void casing(int selection);
};

#endif // TEST_H
