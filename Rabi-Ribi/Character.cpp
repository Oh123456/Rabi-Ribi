#include "Character.h"
#include "PlayerInput.h"

HRESULT Character::Init()
{
	timerInterval = (1.0f / 60.0f);
	TIMERMANAGER->SetTimer(movementTimer,this, &Character::CharaterMove, timerInterval);
	return S_OK;
}

void Character::Release()
{
	TIMERMANAGER->DeleteTimer(movementTimer);
}

void Character::Update()
{
	Super::Update();
	//geomtryLocation = location;
	imageInfo.imageLocation = location;
	if (isFalling)
	{
		// 채공시간이 0.1초 이상이면 추락상태이다
		delayTime += TIMERMANAGER->GettimeElapsed();
		if (delayTime > 0.1f)
		{
			if ((animKinds != AnimmationKinds::Falling) &
				(animKinds != AnimmationKinds::Jum))
				animKinds = AnimmationKinds::Falling;
		}
	}
	else
	{
		delayTime = 0.0f;
		acceleration = 0.0f;
		animKinds = AnimmationKinds::Idle;
	}

}

void Character::MoveGeomtry(Location a)
{
	geomtryLocation = a;
}

void Character::MoveCharacter()
{
	location = geomtryLocation;
	// 카메라가 포커스중인 캐릭터인지 확인
	if (CAMERA->GetFocusActor() == this)
	{
		CAMERA->Update();
		// 카메라 이동에 따른 충돌박스 이동으로 캐릭터 좌표한번더 이동
		location = geomtryLocation;
	}
}

void Character::MoveCancel(bool isSide, bool isUp)
{
	if (isSide)
		geomtryLocation.x = location.x;
	if (isUp)
		geomtryLocation.y = location.y;
	if (isFalling)
		geomtryLocation.y += acceleration;
	MoveCharacter();
}

void Character::MoveToNewGeomtryLocation(const Location & newLocation)
{
	SetGeomtryLocation(newLocation,this->size);
}

void Character::PlayerInputSetting(PlayerInput* playerInput)
{
}

void Character::CharaterMove()
{
	if (isFalling)
	{
		if (acceleration <= 0.0f)
			acceleration = 0.98f*(0.16f);
		acceleration *= 1.03f;
		if (acceleration >= 2.0f)
			acceleration = 2.0f;
		//moveUpValue = acceleration;
		geomtryLocation.y += acceleration;
	}
	this->geomtryLocation.x += (moveSideValue / 60.0f);
	this->geomtryLocation.y += (moveUpValue / 60.0f);

	moveSideValue = 0.0f;
	moveUpValue = 0.0f;
}

