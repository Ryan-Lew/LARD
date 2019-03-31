#ifndef ___MY_SEMAPHORES_H___
#define ___MY_SEMAPHORES_H___

#include <Windows.h>

class Semaphore
{
public:
	Semaphore(UINT32 initial,UINT32 maximum);
	virtual ~Semaphore();
	void Acquire();
	BOOL TryAcquire();
	void Release();
private:
	HANDLE m_handle;
};

#endif
