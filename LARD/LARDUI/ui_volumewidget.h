/********************************************************************************
** Form generated from reading UI file 'volumewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMEWIDGET_H
#define UI_VOLUMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VolumeWidget
{
public:

    void setupUi(QWidget *VolumeWidget)
    {
        if (VolumeWidget->objectName().isEmpty())
            VolumeWidget->setObjectName(QStringLiteral("VolumeWidget"));
        VolumeWidget->resize(400, 300);

        retranslateUi(VolumeWidget);

        QMetaObject::connectSlotsByName(VolumeWidget);
    } // setupUi

    void retranslateUi(QWidget *VolumeWidget)
    {
        VolumeWidget->setWindowTitle(QApplication::translate("VolumeWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VolumeWidget: public Ui_VolumeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMEWIDGET_H
