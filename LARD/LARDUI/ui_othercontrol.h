/********************************************************************************
** Form generated from reading UI file 'othercontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTHERCONTROL_H
#define UI_OTHERCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Othercontrol
{
public:

    void setupUi(QWidget *Othercontrol)
    {
        if (Othercontrol->objectName().isEmpty())
            Othercontrol->setObjectName(QStringLiteral("Othercontrol"));
        Othercontrol->resize(144, 629);

        retranslateUi(Othercontrol);

        QMetaObject::connectSlotsByName(Othercontrol);
    } // setupUi

    void retranslateUi(QWidget *Othercontrol)
    {
        Othercontrol->setWindowTitle(QApplication::translate("Othercontrol", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Othercontrol: public Ui_Othercontrol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTHERCONTROL_H
