#include "Cocoa.h"
#include "CocoaAnimInstance.h"
#include "CocoaAIController.h"

Cocoa::Cocoa()
{
	animmation = CreateObject<CocoaAnimInstance>();
	animmation->SetOwner(this);

	CreateAIController<CocoaAIController>();
}

Cocoa::~Cocoa()
{
}

HRESULT Cocoa::Init()
{
	Super::Init();
	location = { 550.0f,200.0f };
	IMAGEMANAGER->LoadPng(L"Cocoa",L"Chacter/Boss/boss1_a");
	imageInfo.imageName = L"Cocoa";
	imageInfo.atlasInfo.frameSize = { 48.0f,48.0f };
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.affineMatrix = AFFINEMATRIX_3X2_SCALE(1.5f,24.0f);
	imageInfo.imageLocation = location;
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;

	size = { 48.0f,48.0f};

	SetGeomtryCollsion();
	return S_OK;
}

void Cocoa::Release()
{
	Super::Release();
}

void Cocoa::Update()
{
	Super::Update();
}

void Cocoa::Render()
{
	Super::Render();
}

void Cocoa::MoveCharacter(Vector2_F speed)
{
	TimerManager* tiemrManager = TIMERMANAGER;

	if (animKinds == AnimationKinds::Hit)
		return;
	imageInfo.imageLocation = { location.x ,location.y - 20.0f };

	if (speed.x < 0.0f)
	{
		moveSpeed = 50.0f;
		if (animKinds != AnimationKinds::Jump)
		{
			imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.5f,1.5f }, { 24.0f,24.0f });
			animKinds = AnimationKinds::Move_Right;
		}
	}
	else if (speed.x > 0.0f)
	{
		moveSpeed = -50.0f;
		if (animKinds != AnimationKinds::Jump)
		{
			imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, { 24.0f,24.0f });
			animKinds = AnimationKinds::Move_Left;
		}
	}
	else
	{
		if (!isFalling)
		{
			animKinds = AnimationKinds::Idle;
			moveSpeed = 0.0f;
		}
	}
	MoveSideValue(moveSpeed);
}
