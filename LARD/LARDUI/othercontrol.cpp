#include "othercontrol.h"
#include "ui_othercontrol.h"

Othercontrol::Othercontrol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Othercontrol)
{
    ui->setupUi(this);
}

Othercontrol::~Othercontrol()
{
    delete ui;
}
