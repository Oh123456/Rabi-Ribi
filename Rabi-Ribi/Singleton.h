#pragma once

template <typename T>
class Singleton
{
public:
	//�̱��� ��������
	static T* GetSingleton();
	//�̱��� �޸𸮿��� �����ϱ�
	void ReleaseSingleton();

protected:
	Singleton() {}
	virtual ~Singleton() {}



protected:
	//�̱��� �ν��Ͻ� ����
	static T* instance;
};

//�̱��� �ʱ�ȭ
template <typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T * Singleton<T>::GetSingleton()
{
	// �̱����� ������ ���� ��������
	if (!instance)
	{
		instance = new T;
	}

	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	//�̱����� �ִٸ� �޸𸮿��� ��������
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}