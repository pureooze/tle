#ifndef PROMPTERCREATEROOM_H
#define PROMPTERCREATEROOM_H

#include <QDialog>

namespace Ui {
class prompterCreateRoom;
}

class prompterCreateRoom : public QDialog
{
    Q_OBJECT

public:
    explicit prompterCreateRoom(QWidget *parent = 0);
    ~prompterCreateRoom();

private:
    Ui::prompterCreateRoom *ui;

signals:
    void createRoom(QString);

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
};

#endif // PROMPTERCREATEROOM_H
