#pragma once
// 캐스팅 관련


// 다이나믹 캐스트
template<typename T, typename U>
T* Cast(U* src)
{
	return dynamic_cast<T*>(src);
}

// 콘스트 다이나믹 캐스트
template<typename T, typename U>
T* Cast(const U* src)
{
	U* _src = const_cast<U*> (src);
	return dynamic_cast<T*>(_src);
}

// 스타틱 캐스트
template<typename T, typename U>
T Cast(U src)
{
	return static_cast<T>(src);
}

// 콘스트 캐스트
template<typename T, typename U>
T Const_Cast(const U src)
{
	U _src = const_cast<U>(src);
	return static_cast<T>(_src);
}