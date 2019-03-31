#ifndef __SINGLETON__H__
#define __SINGLETON__H__

#include <assert.h>

template <typename T> class Singleton
{
protected:
	static T* m_singleton;
public:
    Singleton( void )
    {
		assert( !m_singleton );
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
        int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
        m_singleton = (T*)((int)this + offset);
#else
		m_singleton = static_cast< T* >( this );
#endif
    }
    ~Singleton( void )
	{  
		assert( m_singleton ); 
		m_singleton = 0;
	}
	static T& GetReference( void )
	{
		assert( m_singleton ); 
		return ( *m_singleton );
	}
	static T* GetPointer( void )
	{
		return m_singleton;
	}
};

#endif
