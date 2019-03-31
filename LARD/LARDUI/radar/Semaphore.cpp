#include "Semaphore.h"




Semaphore::Semaphore(UINT32 initial,UINT32 maximum)
{
	m_handle = CreateSemaphore(	NULL, initial, maximum,NULL);
}

Semaphore::~Semaphore()
{
	CloseHandle(m_handle);
}

void Semaphore::Acquire()
{
	WaitForSingleObject(m_handle,INFINITE);
}
BOOL Semaphore::TryAcquire()
{
	if ( WAIT_OBJECT_0 == WaitForSingleObject(m_handle,0) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void Semaphore::Release()
{
	ReleaseSemaphore(m_handle,1,NULL); 
}
