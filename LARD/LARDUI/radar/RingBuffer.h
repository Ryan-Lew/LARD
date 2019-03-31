#ifndef ___RING_BUFFER_H___
#define ___RING_BUFFER_H___

#include <windows.h>
#include <vector>
#include "Semaphore.h"

class RingBuffer
{
private:
	struct DATA_BLOCK 
	{
		DATA_BLOCK(UINT32 block_size) : m_size(0),m_block(new BYTE[block_size]) {}
		~DATA_BLOCK() { delete[] m_block; }
		UINT32 m_size;
		BYTE*  m_block;
	};
	typedef std::vector<DATA_BLOCK*> DATA_BLOCKS;
public:
	RingBuffer(UINT32 buffer_nums,UINT32 buffer_size);
	virtual ~RingBuffer();
	void Read(BYTE* data,UINT32 size,UINT32* size_read);
	BOOL TryRead(BYTE* data,UINT32 size,UINT32* size_read);
	void Write(const BYTE* data,UINT32 size,UINT32* size_written);
private:
	DATA_BLOCKS  m_buffer;
	Semaphore    m_free_semaphore;
	int          m_free_index;	
	Semaphore    m_used_semaphore;
	int          m_used_index;
	const UINT32 m_buffer_size;
	const UINT32 m_buffer_nums;
};

#endif