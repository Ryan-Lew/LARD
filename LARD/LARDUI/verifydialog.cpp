#include "verifydialog.h"
#include "ui_verifydialog.h"
#include "optiondialog.h"

VerifyDialog::VerifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifyDialog)
{
    //�ޱ߿�
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

VerifyDialog::~VerifyDialog()
{
    delete ui;
}

void VerifyDialog::on_buttonBox_accepted()
{
    OptionDialog dialog;
    if(dialog.exec() ==QDialog::Accepted){

    }
}
