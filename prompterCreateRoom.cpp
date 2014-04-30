#include "prompterCreateRoom.h"
#include "ui_prompterCreateRoom.h"
#include <QDebug>

prompterCreateRoom::prompterCreateRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prompterCreateRoom)
{
    ui->setupUi(this);
}

prompterCreateRoom::~prompterCreateRoom()
{
    delete ui;
}

void prompterCreateRoom::on_cancelButton_clicked()
{
    this->close();
}

void prompterCreateRoom::on_okButton_clicked()
{
    qDebug() << "prompterCreateRoom: starts";

    QString roomName = ui->roomNameLineEdit->text();
    emit createRoom(roomName);

    qDebug() << "prompterCreateRoom: created room, now closing";
    this->close();
}
