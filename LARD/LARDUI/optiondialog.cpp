#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    //�ޱ߿�
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}
