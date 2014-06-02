#ifndef ADDOBJECTDIALOG_H
#define ADDOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class addObjectDialog;
}

class addObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addObjectDialog(QWidget *parent = 0);
    ~addObjectDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addObjectDialog *ui;

signals:
    void objCreation(QStringList);
};

#endif // ADDOBJECTDIALOG_H
