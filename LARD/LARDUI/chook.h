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
     //功能键
    void hook(bool flag);
    //显示任务栏
    void showTaskWindow(bool flag);
     //任务管理器
    void enableTaskManager(bool flag);

private:
    HWND task;

signals:

public slots:


};



#endif // CHOOK_H
