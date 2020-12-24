#pragma once
#include "Character.h"

//player

class Erina : public Character
{
	SUPER(Character);
public:
	Erina();
	~Erina();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	// юс╫ц
	ImageInfo imageInfo;
};

