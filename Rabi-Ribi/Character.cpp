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
		// ä���ð��� 0.1�� �̻��̸� �߶������̴�
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
	// ī�޶� ��Ŀ������ ĳ�������� Ȯ��
	if (CAMERA->GetFocusActor() == this)
	{
		CAMERA->Update();
		// ī�޶� �̵��� ���� �浹�ڽ� �̵����� ĳ���� ��ǥ�ѹ��� �̵�
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

