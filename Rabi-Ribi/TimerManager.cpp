#include "TimerManager.h"
#include "Timer.h"
#include "D2DGraphic.h"


TimerManager::TimerManager()
{
}


TimerManager::~TimerManager()
{
}

HRESULT TimerManager::Init()
{
	timer = new Timer;
	timer->Init();
	timerCount = 0;
	return S_OK;
}

void TimerManager::Release()
{
	Const_IteratorTimerMap it;
	for (it = timers.begin(); it != timers.end(); it++)
		delete it->second;
	delete timer;

	timers.clear();
}

void TimerManager::Update()
{
	timer->Tick();
	this->TimerUpdate();
}

void TimerManager::TimerUpdate()
{
	Const_IteratorTimerMap it;
	std::map<TimerHandle, Timer*> copyTimersmap = timers;
	TimerHandle handle;
	Timer* timer;
	for (it = copyTimersmap.begin(); it != copyTimersmap.end();)
	{
		handle = it->first;
		timer = it->second;
		it++;
		timer->Tick();
		if (timer->GetIsExecutionTimer())
		{
			if (handle.isOnceTimer)
				this->DeleteTimer(handle);
		}
	}
	copyTimersmap.clear();
}

void TimerManager::Render()
{
	if (timer)
	{
		WCHAR text[128];
		swprintf_s(text, 128 ,L"FPS : %d ", timer->GetFPS());
		D2D::GetSingleton()->__DrawText(text, D2D1::RectF(0, 0, 100, 50));

		//WCHAR text[128];
		//swprintf_s(text, 128, L" %d , %d ", g_ptMouse.x, g_ptMouse.y);
		//D2D::GetSingleton()->__DrawText(text, D2D1::RectF(0, 0, 50, 50));

		//wsprintf(szText,"FPS : %d",timer->GetFPS());
		//TextOut(hdc,0,0,szText , (int)strlen(szText));
	}
}

float TimerManager::GettimeElapsed()
{
	return timer->GettimeElapsed();
}

void TimerManager::AllDeleteTimer()
{
	Const_IteratorTimerMap it;
	for (it = timers.begin(); it != timers.end(); it++)
	{
		it->second->timer.UnBind();
		delete it->second;
	}
	timerCount = 0;
	timers.clear();
}

bool TimerManager::ExistTimer(const TimerHandle& timerHandle)
{
	Const_IteratorTimerMap c_it = timers.find(timerHandle);
	if (c_it != timers.end())
		return true;
	return false;
}

void TimerManager::DeleteTimer(TimerHandle & timerHandle)
{
	map<TimerHandle, Timer*>::iterator it;
	it = timers.find(timerHandle);
	if (it != timers.end())
	{
		Timer* newTimer = it->second;
		newTimer->timer.UnBind();
		delete newTimer;
		timers.erase(it);
	}

}