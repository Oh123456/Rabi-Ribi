#include "Erina.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"
#include "PlayerInput.h"
#include "ErinaAnimInstance.h"
#include "Hammer.h"
#include "Rebbon_Weapon.h"

Erina::Erina()
{
	animmation = CreateObject<ErinaAnimInstance>();
	animmation->SetOwner(this);

	pikoHammer = CreateObject<Hammer>();
	pikoHammer->SetOwner(this);

	rebbon = CreateObject<Rebbon_Weapon>();
	rebbon->SetOwner(this);

	moveSpeed = 180.0f;
	damage = 10;
	onHit.BindObject(this,&Erina::OnHit);

	actorType = ActorType::Player;
}

Erina::~Erina()
{

}

HRESULT Erina::Init()
{
	Super::Init();
	location = { 350.0f,200.0f };      
	worldLocation = location;
	size = { 10.0f * 1.5f ,34.0f*1.5f  };
	hitBoxSize = { 0.0f,0.0f };
	imageInfo.imageName = L"Erina";
	imageInfo.imageLocation = location;
	imageInfo.atlasInfo.frameSize = { 64.0f,64.0f };
	imageInfo.atlasInfo.frame = {0,0};
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, { 32.0f,32.0f });
	imageInfo.contrasteInfo.contrast = 1.0f;
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE| D2DIE_CONTRASTEFFECT;
	hp = (int)pow(2,7 * 4);
	SetGeomtryCollsion();
	if (rebbon)
	{
		rebbon->SetLocation({ location });
	}

	return S_OK;
}

void Erina::Release()
{
	Super::Release();
	
}

void Erina::Update()
{
	Super::Update();
}

void Erina::Render()
{
	Super::Render();
}

void Erina::PlayerInputSetting(PlayerInput* playerInput)
{
	Super::PlayerInputSetting(playerInput);
	//playerInput->BindInputKey(VK_UP, KeyInputKinds::StayKey_Down, this, &Erina::MoveUP);
	playerInput->BindInputKey(ZKey, KeyInputKinds::StayKey_Down, this, &Erina::MoveUP);
	playerInput->BindInputKey(ZKey, KeyInputKinds::Key_UP, this, &Erina::MoveUP_KeyUP);

	playerInput->BindInputKey(VK_LEFT, KeyInputKinds::StayKey_Down, this, &Erina::MoveSide);
	playerInput->BindInputKey(VK_RIGHT, KeyInputKinds::StayKey_Down, this, &Erina::MoveSide);

	playerInput->BindInputKey(CKey, KeyInputKinds::Key_Down, this, &Erina::AttackPikoHammer);
	playerInput->BindInputKey(XKey, KeyInputKinds::Key_Down, this, &Erina::RebbonAttack);
	playerInput->BindInputKey(XKey, KeyInputKinds::StayKey_Down, this, &Erina::RebbonChargeAttack);
	playerInput->BindInputKey(XKey, KeyInputKinds::Key_UP, this, &Erina::RebbonChagetAttackFire);
}

void Erina::MoveUP()
{
	if (isMoveLock)
		return;
	// 점프가 끝났으면 초기화
	if (((animKinds != AnimationKinds::Jump) &
		(animKinds != AnimationKinds::Falling)) & (jumKeyDownTime >= JUM_KEYDOWN_TIME))
	{
		jumKeyDownTime = 0.0f;
		acceleration = 0.0f;
	}
	if (KEYMANAGER->GetKeyDown()[ZKey] & (jumKeyDownTime <= JUM_KEYDOWN_TIME))
	{
		this->isFalling = true;
		animKinds = AnimationKinds::Jump;
		if (acceleration == 0.0f)
			acceleration = -9.8f * 0.5f;//(-98.0f * TIMERMANAGER->GetTimeElapsed() * 2.0f);
		else
			acceleration += -9.8f* 0.5f *TIMERMANAGER->GetTimeElapsed();
		jumKeyDownTime += TIMERMANAGER->GetTimeElapsed();
		DEBUG_MASSAGE("%f , %f \n",jumKeyDownTime, acceleration);
	}
}

void Erina::MoveUP_KeyUP()
{
	jumKeyDownTime = 10.0f;
}

void Erina::MoveSide()
{
	if (isMoveLock)
		return;
	if (KEYMANAGER->GetKeyDown()[VK_LEFT])
	{
		MoveSideValue(moveSpeed * -1.0f);
		if (!isFalling)
			animKinds = AnimationKinds::Move_Left;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, { 32.0f,32.0f });
	}
	else if (KEYMANAGER->GetKeyDown()[VK_RIGHT])
	{
		MoveSideValue(moveSpeed * 1.0f);
		if (!isFalling)
			animKinds = AnimationKinds::Move_Right;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.5f,1.5f }, { 32.0f,32.0f });
	}
}

void Erina::AttackPikoHammer()
{
	if (!isMoveLock)
	{
		animKinds = AnimationKinds::Attack1;
		noAnimChange = true;
		isMoveLock = true;
		rebbon->AttackEnd();
	}
	else
	{
		isNextAttack = false;
		rebbon->AttackEnd();
		switch (animKinds)
		{
		case AnimationKinds::Attack1:
		case AnimationKinds::Attack2:
		case AnimationKinds::Attack3:
			isNextAttack = true;
			break;
		case AnimationKinds::Attack4:
			isNextAttack = false;
			break;
		}
	}
}

void Erina::RebbonAttack()
{
	switch (animKinds)
	{
	case AnimationKinds::Attack1:
	case AnimationKinds::Attack2:
	case AnimationKinds::Attack3:
	case AnimationKinds::Attack4:
		break;
	default:
		rebbon->Attack();
		break;
	}
}

void Erina::RebbonChargeAttack()
{
	switch (animKinds)
	{
	case AnimationKinds::Attack1:
	case AnimationKinds::Attack2:
	case AnimationKinds::Attack3:
	case AnimationKinds::Attack4:
	default:
		rebbon->ChargeAttack();
		break;
	}

}

void Erina::RebbonChagetAttackFire()
{
	switch (animKinds)
	{
	case AnimationKinds::Attack1:
	case AnimationKinds::Attack2:
	case AnimationKinds::Attack3:
	case AnimationKinds::Attack4:
	default:
		rebbon->ChargeAttackFire();
		break;
	}

}


void Erina::OnHit(Object* object)
{
	//DEBUG_MASSAGE("충돌처리 체크 \n");
}
