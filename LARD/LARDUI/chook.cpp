#include "chook.h"

#include <QSettings>


//��ע����Ŀ¼������������
#define TASKMANAGERSystem "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
#define TASKMANAGERExplorer "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"

HHOOK keyHook = NULL;
HHOOK mouseHook = NULL;


//���̹��ӹ���
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    //��WH_KEYBOARD_LLģʽ��lParam ��ָ��KBDLLHOOKSTRUCT���͵�ַ
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    //���nCode����HC_ACTION�������Ϣ�����С��0�������ӳ̾ͱ��뽫����Ϣ���ݸ� CallNextHookEx
    if(nCode == HC_ACTION)
    {
        if((pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL)& 0x8000 && GetAsyncKeyState(VK_SHIFT)&0x8000)|| //"Ctrl+Shift+Esc"
            (pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000) || //"Ctrl+Esc"
            (pkbhs->vkCode == VK_TAB && pkbhs->flags & LLKHF_ALTDOWN )|| //"Alt+Tab"
            (pkbhs->vkCode == VK_ESCAPE && pkbhs->flags &LLKHF_ALTDOWN )|| //"Alt+Esc"
            (pkbhs->vkCode == VK_LWIN || pkbhs->vkCode == VK_RWIN )||	// "LWIN/RWIN"
            (pkbhs->vkCode == VK_F4 && pkbhs->flags & LLKHF_ALTDOWN )) //"Alt+F4"
        {
            return 1;//����1��ʾ��ȡ��Ϣ���ٴ���,����0��ʾ��������,��Ϣ��������
        }

        // 		if(pkbhs->vkCode == VK_F12)
        // 		{
        // 			void unHook();
        // 			qApp->quit();
        // 		}
    }
    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}
//��깳�ӹ���
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{

    return 1;

}


CHook::CHook(QObject *parent) : QObject(parent)
{

}


CHook::~CHook()
{

}
//��װ����,���øú�������װ����
void CHook::hook(bool flag)
{
    if (flag)
    {
        //�������ײ㹳��,��ҪDLL�Ϳ���ȫ��
        //�ײ���̹���
        keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
        //�ײ���깳��
        //    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
    }
    else
    {
        UnhookWindowsHookEx(keyHook);
        //  UnhookWindowsHookEx(mouseHook);
    }
}

//���ע������Ctrl+Alt+del
void CHook::enableTaskManager(bool flag)
{
    // ����ctrl + alt +del ��Ҫ�޸�ע����ֵ�� ȡ�ù���ԱȨ�ޣ� �ر�360��ɱ�����
    int value = flag ? 0x00000001 : 0x00000000;
    QSettings *settings = new QSettings(TASKMANAGERSystem, QSettings::NativeFormat);
    settings->setValue("DisableTaskMgr", value); //���������
    settings->setValue("DisableChangePassword", value); //��������
    settings->setValue("DisableLockWorkstation", value); //���������
    settings->setValue("DisableSwitchUserOption", value); //�л��û�

    QSettings *settings2 = new QSettings(TASKMANAGERExplorer, QSettings::NativeFormat);
    settings2->setValue("NoLogOff", value); //ע��

    delete settings;
    delete settings2;
}

//����������
void CHook::showTaskWindow(bool flag)
{
    if(flag)
        ShowWindow(task,SW_SHOW);
    else
    {
        task=FindWindow(L"Shell_TrayWnd",NULL);
        ShowWindow(task,SW_HIDE);
    }
}
