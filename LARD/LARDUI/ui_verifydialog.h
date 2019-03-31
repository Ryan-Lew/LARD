/********************************************************************************
** Form generated from reading UI file 'verifydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFYDIALOG_H
#define UI_VERIFYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VerifyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *usernamelabel;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *passwordlabel;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_4;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VerifyDialog)
    {
        if (VerifyDialog->objectName().isEmpty())
            VerifyDialog->setObjectName(QStringLiteral("VerifyDialog"));
        VerifyDialog->resize(283, 112);
        verticalLayout = new QVBoxLayout(VerifyDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        usernamelabel = new QLabel(VerifyDialog);
        usernamelabel->setObjectName(QStringLiteral("usernamelabel"));

        horizontalLayout_2->addWidget(usernamelabel);

        lineEdit = new QLineEdit(VerifyDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        passwordlabel = new QLabel(VerifyDialog);
        passwordlabel->setObjectName(QStringLiteral("passwordlabel"));

        horizontalLayout->addWidget(passwordlabel);

        lineEdit_2 = new QLineEdit(VerifyDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(VerifyDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setMinimumSize(QSize(280, 30));
        buttonBox->setMaximumSize(QSize(280, 30));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(VerifyDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VerifyDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VerifyDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VerifyDialog);
    } // setupUi

    void retranslateUi(QDialog *VerifyDialog)
    {
        VerifyDialog->setWindowTitle(QApplication::translate("VerifyDialog", "Dialog", nullptr));
        usernamelabel->setText(QApplication::translate("VerifyDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        passwordlabel->setText(QApplication::translate("VerifyDialog", "\345\257\206  \347\240\201\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VerifyDialog: public Ui_VerifyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFYDIALOG_H
