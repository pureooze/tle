#include "prompterRemoveExit.h"
#include "ui_prompterRemoveExit.h"

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

void prompterRemoveExit::setMap(QMap<QString, Room *> *map)
{
    for(auto i : map->keys()){
        ui->targetComboBox->addItem(i);
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
    QString exit = ui->exitLineEdit->text();
    emit removeExit(target, exit);

    qDebug() << "prompterRemoveExit: removed portal, now closing";
    this->close();
}
