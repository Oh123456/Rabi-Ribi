#pragma once
#include "Object.h"
class HPBar : public Object
{
	SUPER(Object);
public:
	void Update() override;
	void Render() override;
	void BindCharacter(class Character* character) { tagetCharacter = character; }
protected:
	class Character* tagetCharacter;
	float hpPersent;
	float hpBarwidth;
	ImageInfo imageinfo;
	ImageInfo HPimageinfo;
};

