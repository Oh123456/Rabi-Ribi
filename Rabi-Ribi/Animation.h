#pragma once
#include "Object.h"


_INTERFACE IAnimation 
{
	virtual void Play() = 0;
	virtual void Stop() = 0;
	virtual bool IsPlaying () = 0;
	virtual bool IsEnd() = 0;
	virtual const Index_2U& GetNowIndex() = 0;
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
	bool IsEnd()		override;
	const Index_2U& GetNowIndex() override;
	void Release()	override;
	void Render(ImageInfo* imageInfo) override;
	void Setting(const Index_2U& startAnimIndex, const Index_2U& endAnimIndex, float speed = 1.0f, bool isLoop = true);
	void SettingLoopIndex(const Index_2U& startAnimIndex, const Index_2U& endAnimIndex);

private:
	void NextIndex();
private:
	Index_2U startAnimIndex;
	Index_2U endAnimIndex;
	Index_2U nowAnimIndex;
	Index_2U loopAnimIndex;
	Index_2U loopendAnimIndex;
	bool isLoop;
	bool isPlaying;
	bool isEnd;
	float speed; 
	
	TimerHandle time;
};
