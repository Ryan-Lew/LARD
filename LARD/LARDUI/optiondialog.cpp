#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <QTranslator>

OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    //ÎÞ±ß¿ò
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::setLanguge(int index)
{
    ui->language->setCurrentIndex(index);
}

void OptionDialog::on_option_ok_btn_clicked()
{
    accept();
}

void OptionDialog::on_option_cancel_btn_clicked()
{
    close();
}

void OptionDialog::on_system_setting_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->system_page);
}


void OptionDialog::on_warning_setting_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->warning_page);
}

void OptionDialog::on_hardware_setting_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->hardware_page);
}

void OptionDialog::on_password_setting_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->password_page);
}



void OptionDialog::updateTr(int index)
{
    QString qmFilename;
    static QTranslator* translator;
    if (translator != NULL)
    {
        qApp->removeTranslator(translator);
        delete translator;
        translator = NULL;
    }
    translator = new QTranslator;

    QString runPath = QCoreApplication::applicationDirPath();       //获取文件运行路径

    if(index == 0)
    {
        qmFilename = runPath + "/lang_Chinese.qm";
    }
    if (index == 1)
    {
        qmFilename = runPath + "/lang_English.qm";
    }
    if (translator->load(qmFilename))
    {
        qApp->installTranslator(translator);
    }
    ui->retranslateUi(this);             // 重新设置界面显示
}

void OptionDialog::on_yuntai_settingleft_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->yuntai_pageleft);
}

void OptionDialog::on_yuntai_settingright_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->yuntai_pageright);
}

void OptionDialog::on_language_currentIndexChanged(int index)
{
    updateTr(index);
    emit signal_changeTr(index);
}
