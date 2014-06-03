#include "addobjectdialog.h"
#include "ui_addobjectdialog.h"
#include <QDebug>

addObjectDialog::addObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addObjectDialog)
{
    ui->setupUi(this);
}

addObjectDialog::~addObjectDialog()
{
    delete ui;
}

void addObjectDialog::on_buttonBox_accepted()
{
    QStringList atr;
    atr << ui->nameEdit->text() << ui->glanceEdit->toPlainText() << ui->examineEdit->toPlainText() << "True" << "False";
    emit objCreation(atr);
}
