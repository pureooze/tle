#ifndef PROMPTERADDEXIT_H
#define PROMPTERADDEXIT_H

#include "room.h"
#include <QDialog>
#include <QMap>

namespace Ui {
class prompterAddExit;
}

class prompterAddExit : public QDialog
{
    Q_OBJECT

public:
    explicit prompterAddExit(QWidget *parent = 0);
    ~prompterAddExit();

    void setMap(QMap<QString, Room *> *map);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::prompterAddExit *ui;

signals:
    void addExit(QString, QString, QString);
};

#endif // PROMPTERADDEXIT_H
