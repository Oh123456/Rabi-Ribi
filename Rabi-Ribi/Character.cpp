#include "Character.h"
#include "PlayerInput.h"
#include "GeometryCollision.h"

HRESULT Character::Init()
{
	timerInterval = (1.0f / 120.0f);
	TIMERMANAGER->SetTimer(movementTimer,this, &Character::CharaterMove, timerInterval,false);
	return S_OK;
}

void Character::Release()
{
	Super::Release();
	TIMERMANAGER->DeleteTimer(movementTimer);
}

#include "Enemy.h"
void Character::Update()
{
	Super::Update();
	//geomtryLocation = location;
	imageInfo.imageLocation = location;
	if (isFalling)
	{
		// 채공시간이 0.1초 이상이면 추락상태이다
		delayTime += TIMERMANAGER->GettimeElapsed();
		if (Cast<Enemy>(this))
			DEBUG_MASSAGE("%f\n", delayTime);
		if (delayTime > 0.17f)
		{
			if ((animKinds != AnimationKinds::Falling) &
				(animKinds != AnimationKinds::Jum))
				animKinds = AnimationKinds::Falling;
		}
	}
	else
	{
		delayTime = 0.0f;
		acceleration = 0.0f;
		if (!noAnimChange)
			animKinds = AnimationKinds::Idle;
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
	//if (isFalling)
	//	geomtryLocation.y += acceleration;
	MoveCharacter();
}

void Character::MoveCancel(bool isSide)
{
	if (isSide)
		geomtryLocation.x = location.x;
}

void Character::MoveToNewGeomtryLocation(const Location & newLocation)
{
	SetGeomtryLocation(newLocation,this->size);
}

void Character::TakeDamage(int damage)
{
	isMoveLock = true;
	animKinds = AnimationKinds::Hit;
	hp -= damage;
	if (hp <= 0)
		this->SetIsValid(false);
}

void Character::PlayerInputSetting(PlayerInput* playerInput)
{
}

void Character::CharaterMove()
{
	if (Cast<Enemy>(this))
		DEBUG_MASSAGE("%f\n", delayTime);
	if (isFalling)
	{
		if (acceleration == 0.0f)
			acceleration = (98.0f * TIMERMANAGER->GettimeElapsed() );
		else
			acceleration += (9.8f * TIMERMANAGER->GettimeElapsed());
		if (acceleration >= 8.0f)
			acceleration = 8.0f;
		//moveUpValue = acceleration;
		geomtryLocation.y += (acceleration);
	}
	this->geomtryLocation.x += (moveSideValue * TIMERMANAGER->GettimeElapsed() * 0.5f);
	this->geomtryLocation.y += (moveUpValue * TIMERMANAGER->GettimeElapsed());

	moveSideValue = 0.0f;
	moveUpValue = 0.0f;
}

