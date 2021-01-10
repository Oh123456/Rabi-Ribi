#include "Character.h"
#include "PlayerInput.h"
#include "GeometryCollision.h"


Character::Character() :
	isFalling(true), hp(0), maxHP(0), damage(0), moveSpeed(0.0f), jumSpeed(0.0f),
	moveSideValue(0.0f), moveUpValue(0.0f), delayTime(0.0f), noAnimChange(false),
	animKinds(AnimationKinds::Idle), isInvincible(false), invincibleTime(2.0f)
{ 
	timerInterval = (1.0f / 120.0f);
	TIMERMANAGER->SetTimer(movementTimer, this, &Character::CharaterMove, timerInterval, false);
	imageInfo.exposureEffectInfo = 0.7f;
};

HRESULT Character::Init()
{
	return S_OK;
}

void Character::Release()
{
	Super::Release();
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
		if (delayTime > 0.17f)
		{
			if ((animKinds != AnimationKinds::Falling) &
				(animKinds != AnimationKinds::Jum) & (animKinds != AnimationKinds::Hit))
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

	if (isInvincible)
	{
		imageInfo.tintColor = Color::RGBAToVector_4f({ 239,238,179,255});
		//imageInfo.tintColor = Color::RGBAToVector_4f({ 255,255,255,255});
		AddImageEffect(imageInfo, D2DIE_TINT);
		AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
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
		//location = geomtryLocation;
	}
	location = geomtryLocation;
	worldLocation = { geomtryLocation.x + cameraLocation.x, geomtryLocation.y + cameraLocation.y };
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
	if (!isInvincible)
	{
		isInvincible = true;
		TIMERMANAGER->SetTimer(hitAnimTimer, this, &Character::HitAnimationTimer, 0.5f);
		TIMERMANAGER->SetTimer(invincibleTimer, this, &Character::InvincibleTimerFun, invincibleTime);
		isMoveLock = true;
		animKinds = AnimationKinds::Hit;
		noAnimChange = true;
		hp -= damage;
		if (hp <= 0)
			this->SetIsValid(false);
	}
}

void Character::PlayerInputSetting(PlayerInput* playerInput)
{

}

void Character::SetInvincibleTimer(float time)
{
	TIMERMANAGER->SetTimer(invincibleTimer, this, &Character::InvincibleTimerFun, time);
}

void Character::SetInvincibleTimer()
{
	this->SetInvincibleTimer(invincibleTime);
}

void Character::CharaterMove()
{
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
	if (!isMoveLock)
	{
		this->geomtryLocation.x += (moveSideValue * TIMERMANAGER->GettimeElapsed());
		this->geomtryLocation.y += (moveUpValue * TIMERMANAGER->GettimeElapsed());

	}
	moveSideValue = 0.0f;
	moveUpValue = 0.0f;
}

void Character::InvincibleTimerFun()
{
	RemoveImageEffect(imageInfo, D2DIE_TINT);
	RemoveImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
	isInvincible = false;
	TIMERMANAGER->DeleteTimer(invincibleTimer);
}

void Character::HitAnimationTimer()
{
	animKinds = AnimationKinds::Idle;
	isMoveLock = false;
	noAnimChange = false;
	TIMERMANAGER->DeleteTimer(hitAnimTimer);
}

