#pragma once
// ĳ���� ����


// ���̳��� ĳ��Ʈ
template<typename T, typename U>
T* Cast(U* src)
{
	return dynamic_cast<T*>(src);
}

// �ܽ�Ʈ ���̳��� ĳ��Ʈ
template<typename T, typename U>
T* Cast(const U* src)
{
	U* _src = const_cast<U*> (src);
	return dynamic_cast<T*>(_src);
}

// ��Ÿƽ ĳ��Ʈ
template<typename T, typename U>
T Cast(U src)
{
	return static_cast<T>(src);
}

// �ܽ�Ʈ ĳ��Ʈ
template<typename T, typename U>
T Const_Cast(const U src)
{
	U _src = const_cast<U>(src);
	return static_cast<T>(_src);
}