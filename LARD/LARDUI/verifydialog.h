#ifndef VERIFYDIALOG_H
#define VERIFYDIALOG_H

#include <QDialog>

namespace Ui {
class VerifyDialog;
}

class VerifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerifyDialog(QWidget *parent = 0);
    ~VerifyDialog();

private slots:



    void on_verifydialog_ok_clicked();

    void on_verifydialog_cancel_clicked();

private:
    Ui::VerifyDialog *ui;
};

#endif // VERIFYDIALOG_H
