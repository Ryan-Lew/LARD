#include "Clock.h"

Clock::Clock()
{
	HANDLE process = GetCurrentProcess();
	/// get the current affinity
#if _MSC_VER >= 1400 && defined (_M_X64)
	GetProcessAffinityMask(process,(PDWORD_PTR)&m_process_affinity_mask,(PDWORD_PTR)&m_system_affinity_mask);
#else
	GetProcessAffinityMask(process,&m_process_affinity_mask,&m_system_affinity_mask);
#endif
	m_thread = GetCurrentThread();
	QueryPerformanceFrequency(&m_performance_frequency);
	m_last_time = 0;
}

Clock::~Clock()
{
}

UINT64 Clock::GetTimeUS()
{
	SetThreadAffinityMask(m_thread,1);
	LARGE_INTEGER performance_counter;
	QueryPerformanceCounter(&performance_counter);
	SetThreadAffinityMask(m_thread,m_process_affinity_mask);
	__int64 quotient  = ((performance_counter.QuadPart) / m_performance_frequency.QuadPart);
	__int64 remainder = ((performance_counter.QuadPart) % m_performance_frequency.QuadPart);
	UINT64 curr_time = (UINT64)quotient * (UINT64)1000000 + ( remainder * (UINT64)1000000 / m_performance_frequency.QuadPart );
	if (curr_time < m_last_time)
	{
		return m_last_time;
	}
	m_last_time = curr_time;
	return curr_time;	
}

UINT64 Clock::GetTimeMS()
{
	return (UINT64)(GetTimeUS() / 1000);
}