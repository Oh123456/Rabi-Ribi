#pragma once
#include "pch.h"
#include "Singleton.h"
class Timer;

struct TimerHandle
{
	bool operator<(const TimerHandle& tm) const
	{
		if (this->timerNum != tm.timerNum)
		{
			if (this->timerNum < tm.timerNum)
				return true;
		}
			return false;
	}

	string timerName;
	// 0���ϰ�� Ÿ�̸Ӵ� ����
	UINT timerNum = 0;
	bool isOnceTimer = false;
};

class TimerManager :public Singleton<TimerManager>
{
	typedef std::map<TimerHandle, Timer*>::const_iterator Const_IteratorTimerMap;


	template<typename UserClass>
	struct Memptr
	{
		typedef typename void(UserClass::* Type)();
	};
public:
	TimerManager();
	~TimerManager();

	HRESULT Init();
	void Release();
	// Ÿ�̸� �Ŵ��� ����Ƽ��
	void Update();
	// ���� Ÿ�̸��� ������Ʈ
	void TimerUpdate();
	// FPS ǥ��
	void Render();

	// ���� Ÿ�̸��� ����
	float GettimeElapsed();

	// ��� Ÿ�̸� ����
	void AllDeleteTimer();
public:
	//isNotDetailedTime true �̸� ���ݴ� ������ Ÿ�̸Ӹ� �����
	template<typename UserClass>
	void SetTimer(TimerHandle& timerHandle, UserClass* object, typename Memptr<UserClass>::Type fun, float delay = 1.0f, bool isNotDetailedTime = true)
	{
		map<TimerHandle, Timer*>::iterator it;
		it = timers.find(timerHandle);
		if (it == timers.end())
		{
			if (timerHandle.timerNum == 0)
			{
				Timer* newTimer = new Timer();
				newTimer->Init(!isNotDetailedTime);
				timerHandle.timerNum = ++timerCount;
				newTimer->SetTimer(object, fun, delay);
				if (timers.find(timerHandle) != timers.end())
					timerHandle.timerNum = ++timerCount;
				timers.insert(make_pair(timerHandle, newTimer));
			}
			else
			{
				Timer* newTimer = new Timer();
				newTimer->Init(!isNotDetailedTime);
				newTimer->SetTimer(object, fun, delay);
				timers.insert(make_pair(timerHandle, newTimer));
			}
		}
		else
		{
 			Timer* newTimer = it->second;
			newTimer->timer.UnBind();
			newTimer->SetTimer(object, fun, delay);
		}
	}

	//isNotDetailedTime true �̸� ���ݴ� ������ Ÿ�̸Ӹ� �����
	// �ѹ��� �����ϴ� Ÿ�̸�
	template<typename UserClass>
	void SetTimer(TimerHandle& timerHandle, UserClass* object, typename Memptr<UserClass>::Type fun, bool isOnceTimer ,float delay = 1.0f, bool isNotDetailedTime = true)
	{
		map<TimerHandle, Timer*>::iterator it;
		it = timers.find(timerHandle);
		if (it == timers.end())
		{
			if (timerHandle.timerNum == 0)
			{
				Timer* newTimer = new Timer();
				newTimer->Init();
				timerHandle.timerNum = ++timerCount;
				timerHandle.isOnceTimer = isOnceTimer;
				newTimer->SetTimer(object, fun, delay);
				timers.insert(make_pair(timerHandle, newTimer));
			}
			else
			{
				Timer* newTimer = new Timer();
				newTimer->Init();
				timerHandle.isOnceTimer = isOnceTimer;
				newTimer->SetTimer(object, fun, delay);
				timers.insert(make_pair(timerHandle, newTimer));
			}
		}
		else
		{
			Timer* newTimer = it->second;
			newTimer->timer.UnBind();
			timerHandle.isOnceTimer = isOnceTimer;
			newTimer->SetTimer(object, fun, delay);
		}
	}

	// Ÿ�̸Ӱ� �����ϴ��� ã�´�.
	bool ExistTimer(const TimerHandle& timerHandle);
	void DeleteTimer(TimerHandle& timerHandle);
private:
	// ���� Ÿ�̸�
	Timer* timer;
	// ����� ���� Ÿ�̸�
	std::map<TimerHandle, Timer*> timers;

	int timerCount;
	char szText[256];
};



#include"Timer.h"