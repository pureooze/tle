#include "addeventdialog.h"
#include "ui_addeventdialog.h"

addEventDialog::addEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEventDialog)
{
    ui->setupUi(this);
}

addEventDialog::~addEventDialog()
{
    delete ui;
}

void addEventDialog::on_buttonBox_accepted()
{
    QStringList atr;
    atr << ui->nameEdit->text();
    emit eventCreation(atr);
}
