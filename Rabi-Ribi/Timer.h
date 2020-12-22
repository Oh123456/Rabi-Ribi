#pragma once
#include "pch.h"
#include "Delegate.h"

DELEGATE(FTimer);

class Timer
{
	template<typename UserClass>
	struct Memptr
	{
		typedef typename void(UserClass::* Type)();
	};
	
public:
	Timer();
	~Timer();

	HRESULT Init(bool isfpsTimeElapsedReset = true);
	void Tick();

	template<typename UserClass>
	void SetTimer(UserClass* object, typename Memptr<UserClass>::Type fun, float delay = 1.0f )
	{
		this->fpsTimeElapsed = 0.0f;
		this->timerDelay = delay;
		this->timer.BindObject(object, fun);
		this->isSetTimer = true;
	}
	void DelteTimer();
	const bool GetIsExecutionTimer() { return isExecutionTimer; }
	const float GettimeElapsed() { return timeElapsed; }
	const ULONG GetFPSFrameCount() { return fpsFrameCount; }
	const ULONG GetFPS() { return fps; }
private:
	// 하드웨어에서 고성능 타이머를 지원하는지
	bool isHardware;
	// 경과 진동수를 초당 진동수로 나눠서 진동수를 시간단위로 변환
	float timeScale;
	// 마지막 시간과 현재 시간의 경과량
	float timeElapsed;
	// 현재 시간(고성능 타이머 값)
	__int64 currTime;
	// 이전시간(고성능 타이머 값)
	__int64 lastTime;
	// 고성능 타이머의 주파수(초당 진동수), 진원하지 않으면 0 반환
	__int64 periodFrequency;
	// 프레임 경과 시간 (1초 확인)
	float fpsTimeElapsed;
	// 초당 프레임 수
	ULONG fpsFrameCount;
	// 프레임수
	ULONG fps;

	// 타이머가 실행됬는지
	bool isExecutionTimer;
	//유저 타이머가 세팅이 됬는지
	bool isSetTimer;
	//n초마다 실행
	float timerDelay;

	bool isfpsTimeElapsedReset;
public:
	//타이머 델리게이트
	FTimer timer;
};

