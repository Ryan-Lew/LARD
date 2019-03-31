#ifndef __BIT_STREAM_H__
#define __BIT_STREAM_H__

#include <vector>
#include <Windows.h>


class BitStream
{
public:
	enum  { MEMORY_ORDER_SAME = 0, MEMORY_ORDER_DIFFERENCE = 1 };
public:
	BitStream(UINT32 order = MEMORY_ORDER_SAME,UINT32 resize_unit = 512) : m_memory_order(order),m_resize_unit(resize_unit),m_size(resize_unit),m_buffer(resize_unit,0),m_used_index(0),m_free_index(0) {}
protected:
	void Write(char value)
	{
		if (m_free_index == m_size )
		{
			m_size += m_resize_unit;
			m_buffer.resize(m_size,0);
		}
		m_buffer[m_free_index] = value;
		++m_free_index;
	}
	bool Read(char& value)
	{
		if (m_used_index < m_free_index)
		{
			value = m_buffer[m_used_index];
			++m_used_index;
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	BitStream& Write(const void* data,UINT32 size)
	{
		const char* v_cc = (const char*)(data);
		for(UINT32 i = 0; i < size; ++i)
		{
			Write(*(v_cc+i));
		}
		return *this;
	}
	const BYTE* Data() const 
	{
		return &m_buffer[m_used_index];
	}

	int Size() const 
	{
		return (m_free_index-m_used_index);	
	}

	void Clear()
	{ 
		m_used_index = 0; 
		m_free_index = 0;
	}
protected:
	std::vector<BYTE> m_buffer;
	UINT32            m_resize_unit;
	UINT32            m_size;
	UINT32            m_memory_order;
	UINT32            m_used_index;
	UINT32            m_free_index;
};


class OutBitStream : public BitStream
{
public:
	OutBitStream(UINT32 order = MEMORY_ORDER_SAME,UINT32 resize_unit = 1024) : BitStream(order,resize_unit) {}
	template <class T> OutBitStream& operator<<(T value)
	{
		const char* v_cc = (const char*)(&value);
		UINT32 size = sizeof(T);
		for(UINT32 i = 0; i < size; ++i)
		{
			if (MEMORY_ORDER_SAME == m_memory_order)
			{
				Write( v_cc[i] );
			}
			else
			{
				Write( v_cc[size-1-i]);
			}			
		}
		return *this;
	}
};


class InBitStream : public BitStream
{
public:
	
	InBitStream(UINT32 order = MEMORY_ORDER_SAME,UINT32 resize_unit = 1024) : BitStream(order,resize_unit) {}
	InBitStream(const char* data,UINT32 size,UINT32 order = MEMORY_ORDER_SAME,UINT32 resize_unit = 32) : BitStream(order,resize_unit)
	{
		Write(data,size);
	}
	template <class T> InBitStream& operator>>(T& value)
	{
		char* v_c = (char*)&value;
		UINT32 size = sizeof(T);
		for (UINT32 i = 0; i < size; ++i)
		{
			if (MEMORY_ORDER_SAME == m_memory_order)
			{
				Read(v_c[i]);
			}
			else
			{
				Read(v_c[size-1- i]);
			}
		}
		return *this;
	}	
};



#endif
