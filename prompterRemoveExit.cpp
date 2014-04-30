#include "prompterRemoveExit.h"
#include "ui_prompterRemoveExit.h"
#include "room.h"
#include <QMap>

prompterRemoveExit::prompterRemoveExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prompterRemoveExit)
{
    ui->setupUi(this);
}

prompterRemoveExit::~prompterRemoveExit()
{
    delete ui;
}

void prompterRemoveExit::setMap(QMap<QString, Room *> *rooms)
{
    for(auto i : rooms->keys()){
        ui->targetComboBox->addItem(i);
    }

    this->portals = (*rooms).value(ui->targetComboBox->currentText())->getPortals();
    data = new QMap<QString, Room *>;

    for(auto i : rooms->keys()){
        data->insert(i, rooms->value(i));
        qDebug() << data->values();
    }
//    for(auto i : portals.keys()){
//        ui->portalComboBox->addItem(i);
//        QString bob = portals.value(i);
//        qDebug() << i << bob;
//        data->insert(i, bob);
//        qDebug() << data->values();
//    }
}

void prompterRemoveExit::on_cancelButton_clicked()
{
    this->close();
}

void prompterRemoveExit::on_okButton_clicked()
{
    qDebug() << "prompterRemoveExit: OK pressed, sending signal";

    QString target = ui->targetComboBox->currentText();
    QString exit = ui->portalComboBox->currentText();
    emit removeExit(target, exit);

    qDebug() << "prompterRemoveExit: removed portal, now closing";
    this->close();
}



void prompterRemoveExit::on_targetComboBox_currentIndexChanged(int index)
{
    qDebug() << index;
}
