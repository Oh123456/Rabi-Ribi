#pragma once
#include "ObjectBase.h"
enum class RebbonAnimationKinds
{
	Idle,
};

class Rebbon : public ObjectBase
{
public:
	Rebbon();
	virtual ~Rebbon();

	void SetAinimationKinds(RebbonAnimationKinds kinds) { anim = kinds; }
	RebbonAnimationKinds GetAinimationKinds() { return anim; }
protected:
	RebbonAnimationKinds anim;
};

