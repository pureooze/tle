#ifndef PROMPTERREMOVEEXIT_H
#define PROMPTERREMOVEEXIT_H

#include "room.h"
#include <QDialog>
#include <QMap>
#include <QList>

namespace Ui {
class prompterRemoveExit;
}

class prompterRemoveExit : public QDialog
{
    Q_OBJECT

public:
    explicit prompterRemoveExit(QWidget *parent = 0);
    ~prompterRemoveExit();

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();

    void on_targetComboBox_currentIndexChanged(int index);

public slots:
    void setMap(QMap<QString, Room *> rooms);

private:
    Ui::prompterRemoveExit *ui;
    QMap<QString, Room *> *data;
    QList< QMap<QString, QString> > *portals;
//    QMap<QString, QString> portals;

signals:
    void removeExit(QString, QString);

};

#endif // PROMPTERREMOVEEXIT_H
