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

void prompterAddExit::setMap(QMap<QString, Room *> *map)
{
    foreach(QString i, map->keys()){
        ui->addToComboBox->addItem(i);
        ui->targetComboBox->addItem(i);
    }
}

void prompterAddExit::on_okButton_clicked()
{
    qDebug() << "prompterAddExit: starts";

    QString roomName = ui->addToComboBox->currentText();
    QString portalName = ui->exitLineEdit->text();
    QString targetName = ui->targetComboBox->currentText();
    emit addExit(roomName, portalName, targetName);

    qDebug() << "prompterAddExit: added portal, now closing";
    this->close();
}

void prompterAddExit::on_cancelButton_clicked()
{
    this->close();
}
