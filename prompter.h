#ifndef PROMPTER_H
#define PROMPTER_H

#include <QDialog>

namespace Ui {
class prompter;
}

class prompter : public QDialog
{
    Q_OBJECT

public:
    explicit prompter(QWidget *parent = 0);
    ~prompter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::prompter *ui;

signals:
    void settingsSent();
};

#endif // PROMPTER_H
