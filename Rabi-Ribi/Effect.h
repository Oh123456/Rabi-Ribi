#pragma once
#include "Actor.h"

#define EFFECTKINDS(x,y) ((x << 16)|(y))
// HIWORD x축 , LOWORD y축
enum class EffectKinds : DWORD
{
	Small_Blue_Effect,
	Carrot_Bomb,
	Carrot_Bomb_Explosion,
	Black_Bomb,
	Black_Bomb_Explosion,
};


_INTERFACE IEffect
{
	virtual void SetOwner(Actor* actor) = 0;
	virtual void SetSocketLocation(Location location) = 0;
	virtual void SetEffect(EffectKinds effectKinds) = 0;
};

_INTERFACE IEffectBody;

class Effect : public Actor ,public IEffect
{
	SUPER(Actor);
public:
	Effect() : owner(nullptr), body(nullptr) 
	{
		IgnoreTerrain = true;
	}

	void SetOwner(Actor* actor) override  { owner = actor; }
	void SetSocketLocation(Location location) override { this->location = location; }
	void SetEffect(EffectKinds effectKinds) override;
	const IEffectBody* GetEffect() const { return body; }

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

protected:
	Actor* owner;
	IEffectBody* body;
};

#define EFFECTKINDS(x,y) ((x << 16)|(y))
_INTERFACE IEffectBody
{
	virtual void Render(ImageInfo& imageInfo) = 0;
	virtual void Update(ImageInfo& imageInfo) = 0;
	virtual void Release(ImageInfo& imageInfo)	= 0;
};

class EffectBody : public IEffectBody
{
public:
	void Render(ImageInfo& imageInfo) override { };
protected:
	// HIWORD x축 , LOWORD y축
	enum class EffectFrame : DWORD
	{
		Small_Blue_Frame = EFFECTKINDS(4, 3),
		Carrot_Bomb_Frame = EFFECTKINDS(0, 1),
		Black_Bomb_Frame = EFFECTKINDS(7, 1),
		Red_Explosion_Frame = EFFECTKINDS(1, 2),
		Blue_Explosion_Frame = EFFECTKINDS(5, 2),
		White_Explosion_Frame = EFFECTKINDS(0, 2),
	};
};