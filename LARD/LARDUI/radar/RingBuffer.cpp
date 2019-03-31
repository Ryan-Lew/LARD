#include "RingBuffer.h"
#include <Windows.h>


RingBuffer::RingBuffer(UINT32 buffer_nums,UINT32 buffer_size) :
m_buffer_nums(buffer_nums),
m_buffer_size(buffer_size),
m_buffer(buffer_nums,NULL),
m_free_semaphore(buffer_nums,buffer_nums),
m_used_semaphore(0,buffer_nums),
m_used_index(0),
m_free_index(0)
{
	for (UINT32 i = 0; i < m_buffer_nums; ++i)
	{
		m_buffer[i] = new DATA_BLOCK(buffer_size);
	}
}

RingBuffer::~RingBuffer()
{
	for (UINT32 i = 0; i < m_buffer_nums; ++i)
	{
		delete  m_buffer[i];
		m_buffer[i] = NULL;
	}
	m_buffer.clear();
}

void RingBuffer::Read(BYTE* data,UINT32 size,UINT32* size_read)
{
	*size_read = 0;
	m_used_semaphore.Acquire();
	DATA_BLOCK* source = m_buffer[m_used_index];
	*size_read = ( source->m_size < size ) ? source->m_size : size;
	CopyMemory(data,source->m_block,*size_read);	
	m_used_index  = (m_used_index + 1) % m_buffer_nums;
	m_free_semaphore.Release();
}

BOOL RingBuffer::TryRead(BYTE* data,UINT32 size,UINT32* size_read)
{
	*size_read = 0;
	if (m_used_semaphore.TryAcquire())
	{
		DATA_BLOCK* source = m_buffer[m_used_index];
		*size_read = ( source->m_size < size ) ? source->m_size : size;
		CopyMemory(data,source->m_block,*size_read);	
		m_used_index  = (m_used_index + 1) % m_buffer_nums;
		m_free_semaphore.Release();
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

void RingBuffer::Write(const BYTE* data,UINT32 size,UINT32* size_written)
{
	*size_written = 0;
	m_free_semaphore.Acquire();
	DATA_BLOCK* desti = m_buffer[m_free_index];
	desti->m_size= (size < m_buffer_size) ? size : m_buffer_size;
	*size_written = desti->m_size;
	CopyMemory(desti->m_block,data,desti->m_size);	
	m_free_index  = (m_free_index + 1) % m_buffer_nums;
	m_used_semaphore.Release();
}