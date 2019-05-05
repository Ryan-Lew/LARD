#include "verifydialog.h"
#include "ui_verifydialog.h"

VerifyDialog::VerifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifyDialog)
{
    //ÎÞ±ß¿ò
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

VerifyDialog::~VerifyDialog()
{
    delete ui;
}




void VerifyDialog::on_verifydialog_ok_clicked()
{
    accept();


}

void VerifyDialog::on_verifydialog_cancel_clicked()
{
    close();
}
