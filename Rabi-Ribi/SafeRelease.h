#pragma once
// 안전 메모리 해제


#define SAFE_DELETE(x) \
if (x) \
{\
	delete x;\
	x = nullptr; \
}

#define SAFE_ARR_DELETE(x) \
if (x) \
{\
	delete[] x;\
	x = nullptr; \
}

#define SAFE_RELEASE(x) \
 if (x)\
{ \
 	x->Release(); \
	x = nullptr; \
}

template<typename T>
void SafeSTLRelease(T& stl)
{
	typename T::iterator it;
	for (it = stl.begin(); it != stl.end(); it++)
	{
		SAFE_RELEASE(*it);
	}
	stl.clear();
}

template<typename T>
void SafemapRelease(T& stl)
{
	typename T::iterator it;
	for (it = stl.begin(); it != stl.end(); it++)
	{
		SAFE_RELEASE(it->second);
	}
	stl.clear();
}


