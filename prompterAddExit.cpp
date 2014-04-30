#include "prompterAddExit.h"
#include "ui_prompterAddExit.h"
#include <QDebug>

prompterAddExit::prompterAddExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prompterAddExit)
{
    ui->setupUi(this);
}

prompterAddExit::~prompterAddExit()
{
    delete ui;
}

void prompterAddExit::on_okButton_clicked()
{
    qDebug() << "prompterAddExit has submitted";

    QString roomName = ui->addToComboBox->currentText();
    roomName = "Desert";
    QString exitName = ui->exitLineEdit->text();
    exitName = "caveEntrance";
    QString targetName = ui->targetComboBox->currentText();
    targetName = "Cave";
    emit addExit(roomName, exitName, targetName);

    qDebug() << "prompterAddExit has added exits, now closing";
    this->close();
}

void prompterAddExit::setMap(QMap<QString, Room *> *map)
{
    for(auto i : map->keys()){
        ui->addToComboBox->addItem(i);
        ui->targetComboBox->addItem(i);
    }
}

void prompterAddExit::on_cancelButton_clicked()
{
    this->close();
}
