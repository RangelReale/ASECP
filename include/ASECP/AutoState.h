#ifndef H__ASECP_AUTOSTATE__H
#define H__ASECP_AUTOSTATE__H

#include <ASECP/Exceptions.h>

#include <algorithm>

namespace ASECP {


template <class C>
class AutoState
{
public:
	AutoState(C* ptr): _ptr(ptr), _r(-1)
	{
		if (_ptr) 
		{
			_r = _ptr->PushState();
			if (_r < 0)
				_ptr = NULL;
		}
	}

	~AutoState()
	{
		if (_ptr) _ptr->PopState();
	}

	C* operator -> ()
	{
		if (_ptr)
			return _ptr;
		else
			throw NullPointerException();
	}

	const C* operator -> () const
	{
		if (_ptr)
			return _ptr;
		else
			throw NullPointerException();
	}

	C& operator * ()
	{
		if (_ptr)
			return *_ptr;
		else
			throw NullPointerException();
	}

	const C& operator * () const
	{
		if (_ptr)
			return *_ptr;
		else
			throw NullPointerException();
	}

	C* get()
	{
		return _ptr;
	}

	const C* get() const
	{
		return _ptr;
	}

	operator C* ()
	{
		return _ptr;
	}
	
	operator const C* () const
	{
		return _ptr;
	}
	
	bool operator ! () const
	{
		return _ptr == 0;
	}

	bool isNull() const
	{
		return _ptr == 0;
	}

	int r()
	{
		return _r;
	}

	int r() const
	{
		return _r;
	}

private:
	C* _ptr;
	int _r;
};

} // ASECP

#endif // H__ASECP_AUTOSTATE__H
