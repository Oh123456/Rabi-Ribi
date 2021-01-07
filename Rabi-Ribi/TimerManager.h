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
	// 0번일경우 타이머는 없다
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
	// 타이머 매니저 업데티으
	void Update();
	// 유터 타이머의 업데이트
	void TimerUpdate();
	// FPS 표시
	void Render();

	// 월드 타이머의 간격
	float GettimeElapsed();

	// 모든 타이머 삭제
	void AllDeleteTimer();
public:
	//isNotDetailedTime true 이면 조금더 정밀한 타이머를 만든다
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

	//isNotDetailedTime true 이면 조금더 정밀한 타이머를 만든다
	// 한번만 실행하는 타이머
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

	// 타이머가 존재하는지 찾는다.
	bool ExistTimer(const TimerHandle& timerHandle);
	void DeleteTimer(TimerHandle& timerHandle);
private:
	// 월드 타이머
	Timer* timer;
	// 사용자 유저 타이머
	std::map<TimerHandle, Timer*> timers;

	int timerCount;
	char szText[256];
};



#include"Timer.h"