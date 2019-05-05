#ifndef __MY_CLOCK_H__
#define __MY_CLOCK_H__

#include <Windows.h>

class Clock
{
public:
	Clock();
	~Clock();
	UINT64 GetTimeUS();
	UINT64 GetTimeMS();
private:
	DWORD  m_process_affinity_mask;
	DWORD  m_system_affinity_mask;
	HANDLE m_thread;
	LARGE_INTEGER m_performance_frequency;
	UINT64 m_last_time;	
};

#endif