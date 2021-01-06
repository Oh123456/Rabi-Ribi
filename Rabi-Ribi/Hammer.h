#pragma once
#include "Weapon.h"

enum class HammerAnimationKinds
{
	None,
	Attack_1,
	Attack_2,
	Attack_3,
	Attack_4,
};

enum class AttackKinds
{
	OneHit,
	AllHit,
};

class Hammer : public Weapon
{
	SUPER(Weapon);
public:
	Hammer();
	~Hammer();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;


	inline void SetAnimationKinds(HammerAnimationKinds animKinds) { this->animKinds = animKinds; }
	inline HammerAnimationKinds GetAnimationKinds() const { return animKinds; }
	void ClearHitObject() { hitobjects.clear(); }
private:
	void OnHit(Object* object);
private:
	HammerAnimationKinds animKinds;
	AttackKinds attackKinds;
	deque<Actor*> hitobjects;
};

