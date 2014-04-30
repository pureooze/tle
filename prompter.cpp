#include "prompter.h"
#include "ui_prompter.h"
#include <QDebug>

prompter::prompter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prompter)
{
    ui->setupUi(this);
}

prompter::~prompter()
{
    delete ui;
}

void prompter::on_pushButton_clicked()
{
    qDebug() << "press";
    emit settingsSent();
}
