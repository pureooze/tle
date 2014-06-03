#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class addEventDialog;
}

class addEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addEventDialog(QWidget *parent = 0);
    ~addEventDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addEventDialog *ui;

signals:
    void eventCreation(QStringList);
};

#endif // ADDEVENTDIALOG_H
