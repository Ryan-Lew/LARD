#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include <Windows.h>


class Thread
{
public:
	Thread() : m_handle(NULL) {}
	virtual ~Thread() {}
	BOOL Start();
	void Wait();
protected:
	virtual void Run() = 0;
protected:
	HANDLE  m_handle;
protected:
	static DWORD WINAPI ThreadWorker(LPVOID my_thread);
};

#endif


