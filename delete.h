#ifndef DELETE_H
#define DELETE_H

#include <QDialog>

namespace Ui {
class Delete;
}

class Delete : public QDialog
{
    Q_OBJECT

public:
    explicit Delete(QWidget *parent = 0);
    ~Delete();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::Delete *ui;
};

#endif // DELETE_H
