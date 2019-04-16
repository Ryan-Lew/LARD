#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = 0);
    ~OptionDialog();
    void setLanguge(int index);
signals:
    void signal_changeTr(int index);
private slots:
    void on_option_ok_btn_clicked();

    void on_option_cancel_btn_clicked();

    void on_system_setting_clicked();


    void on_warning_setting_clicked();

    void on_hardware_setting_clicked();

    void on_password_setting_clicked();

    void updateTr(int index);
    void on_yuntai_settingleft_clicked();

    void on_yuntai_settingright_clicked();

    void on_language_currentIndexChanged(int index);

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
