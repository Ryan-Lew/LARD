/********************************************************************************
** Form generated from reading UI file 'lardvideo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARDVIDEO_H
#define UI_LARDVIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LardVideo
{
public:

    void setupUi(QWidget *LardVideo)
    {
        if (LardVideo->objectName().isEmpty())
            LardVideo->setObjectName(QStringLiteral("LardVideo"));
        LardVideo->resize(400, 300);

        retranslateUi(LardVideo);

        QMetaObject::connectSlotsByName(LardVideo);
    } // setupUi

    void retranslateUi(QWidget *LardVideo)
    {
        LardVideo->setWindowTitle(QApplication::translate("LardVideo", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LardVideo: public Ui_LardVideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARDVIDEO_H
