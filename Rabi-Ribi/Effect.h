#pragma once
#include "Actor.h"

#define EFFECTKINDS(x,y) ((x << 16)|(y))
// HIWORD x축 , LOWORD y축
enum class EffectKinds : DWORD
{
	Small_Blue_Effect,
};


_INTERFACE IEffect
{
	virtual void SetOwner(Actor* actor) = 0;
	virtual void SetSocketLocation(Location location) = 0;
	virtual void SetEffect(EffectKinds effectKinds) = 0;
};

_INTERFACE IEffectBoday;

class Effect : public Actor ,public IEffect
{
	SUPER(Actor);
public:

	void SetOwner(Actor* actor) override  { owner = actor; }
	void SetSocketLocation(Location location) override { this->location = location; }
	void SetEffect(EffectKinds effectKinds) override;

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

protected:
	Actor* owner;
	IEffectBoday* body;
};

#define EFFECTKINDS(x,y) ((x << 16)|(y))
_INTERFACE IEffectBoday
{
	virtual void Update(ImageInfo& imageInfo) = 0;
	virtual void Release(ImageInfo& imageInfo)	= 0;
};

class EffectBoday : public IEffectBoday
{
protected:
	// HIWORD x축 , LOWORD y축
	enum class EffectFrame : DWORD
	{
		Small_Blue_Frame = EFFECTKINDS(4, 3)
	};
};