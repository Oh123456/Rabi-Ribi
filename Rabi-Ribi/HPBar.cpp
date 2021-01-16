#include "HPBar.h"
#include "Character.h"

void HPBar::Update()
{
	Super::Update();
	if (tagetCharacter)
	{
		float MaxHP = (float)tagetCharacter->GetMaxHP();
		float HP = (float)tagetCharacter->GetHP();

		hpPersent = HP / MaxHP;


		HPimageinfo.atlasInfo.frameSize.width = (hpBarwidth * hpPersent);
	}
}

void HPBar::Render()
{
	Super::Render();
	IMAGEMANAGER->ImageRander(HPimageinfo);
	IMAGEMANAGER->ImageRander(imageinfo);
}
