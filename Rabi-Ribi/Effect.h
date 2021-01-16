#pragma once
#include "Actor.h"
#include "EffectIndex.h"

#define EFFECTKINDS(x,y) ((x << 16)|(y))
// HIWORD x축 , LOWORD y축
enum class EffectKinds : DWORD
{
	Small_Blue_Effect,
	Carrot_Bomb,
	Carrot_Bomb_Explosion,
	Black_Bomb,
	Black_Bomb_Explosion,
	Blue_Projectlie,
	Red_Projectlie,
	Flashing_Rotation_Effect,
	None,
};


_INTERFACE IEffectBody;


#define EFFECTKINDS(x,y) ((x << 16)|(y))
_INTERFACE IEffectBody
{
	virtual void Render(ImageInfo& imageInfo) = 0;
	virtual void Update(ImageInfo& imageInfo) = 0;
	virtual void Release(ImageInfo& imageInfo)	= 0;
	virtual HRESULT SetValue(UINT index, const void* data) = 0;
};

class EffectBody : public IEffectBody
{
	
public:
	// HIWORD x축 , LOWORD y축
	enum class EffectFrame : DWORD
	{
		Small_Blue_Frame = EFFECTKINDS(4, 3),
		Carrot_Bomb_Frame = EFFECTKINDS(0, 1),
		Black_Bomb_Frame = EFFECTKINDS(7, 1),
		Red_Explosion_Frame = EFFECTKINDS(1, 2),
		Blue_Explosion_Frame = EFFECTKINDS(5, 2),
		White_Explosion_Frame = EFFECTKINDS(0, 2),
		Blue_Projectlie_Frame = EFFECTKINDS(25, 1),
		Red_Projectlie_Frame = EFFECTKINDS(22, 7),
		Blue_EllipseProjectlie_Frame = EFFECTKINDS(24, 5),
		SkyBlue_EllipseProjectlie_Frame = EFFECTKINDS(25, 5),
	};
public:
	void Render(ImageInfo& imageInfo) override { };
	void SetEffectFrame(EffectFrame frame) { effectframe = frame; }

protected:
	EffectFrame effectframe;
};



_INTERFACE IEffect
{
	virtual void SetOwner(Actor* actor) = 0;
	virtual void SetSocketLocation(Location location) = 0;
	virtual void SetEffect(EffectKinds effectKinds) = 0;
	virtual void SetEffectFrame(EffectBody::EffectFrame frame) = 0;
	template<typename T>
	HRESULT SetValue(UINT index, T& data)
	{
		this->SetValue(index,&data);
	}
private:
	virtual HRESULT SetValue(UINT index, const void* data) = 0;
};


class Effect : public Actor, public IEffect
{
	SUPER(Actor);
public:
	Effect() : owner(nullptr), body(nullptr)
	{
		IgnoreTerrain = true;
	}

	void SetOwner(Actor* actor) override { owner = actor; }
	void SetSocketLocation(Location location) override { this->location = location; }
	void SetEffect(EffectKinds effectKinds) override;
	const IEffectBody* GetEffect() const { return body; }
	void SetEffectFrame(EffectBody::EffectFrame frame);

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	HRESULT SetValue(UINT index, const void* data) override
	{
		return body->SetValue(index, (&data));
	}

protected:
	Actor* owner;
	IEffectBody* body;
};

