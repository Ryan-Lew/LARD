#ifndef CHOOK_H
#define CHOOK_H

#include <QObject>
#include <windows.h>

class CHook : public QObject
{
    Q_OBJECT
public:
    explicit CHook(QObject *parent = nullptr);
    ~CHook();

private:
     //���ܼ�
    void hook(bool flag);
    //��ʾ������
    void showTaskWindow(bool flag);
     //���������
    void enableTaskManager(bool flag);

private:
    HWND task;

signals:

public slots:


};



#endif // CHOOK_H
