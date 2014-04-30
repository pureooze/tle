#ifndef PROMPTERREMOVEEXIT_H
#define PROMPTERREMOVEEXIT_H

#include "room.h"
#include <QDialog>
#include <QMap>

namespace Ui {
class prompterRemoveExit;
}

class prompterRemoveExit : public QDialog
{
    Q_OBJECT

public:
    explicit prompterRemoveExit(QWidget *parent = 0);
    ~prompterRemoveExit();

    void setMap(QMap<QString, Room *> *map);

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::prompterRemoveExit *ui;

signals:
    void removeExit(QString, QString);

};

#endif // PROMPTERREMOVEEXIT_H
