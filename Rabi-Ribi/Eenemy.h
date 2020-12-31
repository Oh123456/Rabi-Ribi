#pragma once
#include "Character.h"
class Eenemy : public Character
{
	SUPER(Character);
public:
	Eenemy();
	~Eenemy();

	void Update()	override;
	void MoveCharacter() override;

protected:
	Location worldLocation;
	// 충돌처리 전까지 플레이어가 움직이면 카메라의 좌표가 
	//변함으로 실제 위치와 다르게 되서 처음 위치구했을때의 
	//값을 저장해둔 변수
	Location cameraLocation;
};

