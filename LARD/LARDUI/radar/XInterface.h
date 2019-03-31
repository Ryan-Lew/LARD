#ifndef ___X_INTERFACE_H__
#define ___X_INTERFACE_H__

#include <QWidget>

class QAbstractButton;

class XInterface : public QWidget
{
	Q_OBJECT
public:
    XInterface(QWidget* parent) : QWidget(parent) {}
	virtual ~XInterface() {}


};


#endif
