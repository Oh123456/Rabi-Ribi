#pragma once
#include "Weapon.h"

enum class ProjectileAnimationKinds
{
	None,
	Circle_Red,
	Circle_Blue,
	Circle_Green,
	Circle_Purple,
	Missile_Blue,
	Missile_Red,
	Missile_Green,
};

enum class MovePatten : int
{
	Nomal,
	Angle,
	AngleTun,
	End,
};

const int MovePattenEnd = Cast<int>(MovePatten::End);

class Projectile : public Weapon
{
	SUPER(Weapon);

	typedef void(Projectile::* Funptr)();
public:
	Projectile();
	~Projectile() {};

	 HRESULT Init()	override;
	 void Release()	override;
	 void Update()	override;
	 void Render()	override;
	 void SetIsValid(bool value) override;

	 void MoveSetting(float angle, Vector2_F speed, MovePatten movePatten);

	 void SetAngle(float angle)								{ this->angle = angle; }
	 virtual void SetSpeed(Vector2_F speed)							{ this->speed = speed; }
	 void SetMovePatten(MovePatten movePatten)			{ this->movePatten = movePatten; }

	 float GetAngle()										const { return this->angle; }
	 Vector2_F GetSpeed()								const { return this->speed; }
	 MovePatten GetMovePatten()						const { return this->movePatten; }
	 
	 void SetProjectileAnimationKinds(ProjectileAnimationKinds kinds) { animKinds = kinds; }
	 ProjectileAnimationKinds GetProjectileAnimationKinds() { return animKinds; }

	 void CreateEffect();
	 _INTERFACE IEffect* GetEffect() { return effect; }

private:
	void OnHit(Object* object);
	void MoveMent() override;
	void NomalMovePatten();
	void AngleMovePatten();
	void AngleTunMovePatten();
	void AngleTun();
protected:
	ProjectileAnimationKinds animKinds;
	//float angle;
	Vector2_F speed;

	MovePatten movePatten;

	vector<Funptr> vcMovePatten;
	Location worldLocation;
	_INTERFACE IEffect* effect;

	ImageInfo defaultImageInfo;
	TimerHandle angleTunTimer;
};

