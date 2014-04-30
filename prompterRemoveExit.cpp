#include "prompterRemoveExit.h"
#include "ui_prompterRemoveExit.h"
#include "room.h"
#include <QMap>

prompterRemoveExit::prompterRemoveExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prompterRemoveExit)
{
    ui->setupUi(this);
    portals = new QList< QMap<QString, QString> >;
}

prompterRemoveExit::~prompterRemoveExit()
{
    delete ui;
}

void prompterRemoveExit::setMap(QMap<QString, Room *> rooms)
{
    qDebug() << "prompterRemoveExit: rooms recieved, starting";
    for(auto i : rooms.keys()){
        ui->targetComboBox->addItem(i);
        portals->append(rooms.value(i)->getPortals());
    }
    qDebug() << "prompterRemoveExit: rooms added to db, ending";
    if(portals->length() > 1){
        ui->targetComboBox->setCurrentIndex(1);
        ui->targetComboBox->setCurrentIndex(0);
    }else{
        qDebug() << "0";
    }
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
    ui->portalComboBox->clear();
    for(auto i : portals->value(index).keys()){
        ui->portalComboBox->addItem(i);
    }
}
