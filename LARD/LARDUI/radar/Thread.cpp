#include "Thread.h"


BOOL Thread::Start()
{
	DWORD thread_id;
	m_handle = CreateThread(NULL,0,Thread::ThreadWorker,(LPVOID)this,0,&thread_id);
	if(m_handle)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

void Thread::Wait()
{
	if (m_handle)
	{
		WaitForSingleObject(m_handle,INFINITE);
		CloseHandle(m_handle);
	}
}



DWORD WINAPI Thread::ThreadWorker(LPVOID my_thread)
{
	static_cast<Thread*>(my_thread)->Run();
	return 0;
}
