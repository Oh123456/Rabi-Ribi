#pragma once
#include "Object.h"


_INTERFACE IAnimation 
{
	virtual void Play() = 0;
	virtual void Stop() = 0;
	virtual bool IsPlaying () = 0;
	virtual bool IsRevers() = 0;
	virtual void Release() = 0;
	virtual void Render(ImageInfo* imageInfo) = 0;
};

class Animation : public IAnimation
{
public:
	Animation();
	~Animation();

	void Play()		override;
	void Stop()		override;
	bool IsPlaying()	override;
	bool IsRevers()	override;
	void Release()	override;
	void Render(ImageInfo* imageInfo) override;
	void Setting(const Index_2U& startAnimIndex, const Index_2U& endAnimIndex, float speed = 1.0f, bool isLoop = true, bool isRevers = false);

private:
	void NextIndex();
private:
	Index_2U startAnimIndex;
	Index_2U endAnimIndex;
	Index_2U nowAnimIndex;
	bool isLoop;
	bool isPlaying;
	bool isRevers;
	float speed; 
	
	TimerHandle time;
};
