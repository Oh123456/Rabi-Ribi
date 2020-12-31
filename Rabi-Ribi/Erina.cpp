#include "Erina.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"
#include "PlayerInput.h"
#include "ErinaAnimInstance.h"
#include "Hammer.h"

Erina::Erina()
{
	animmation = CreateObject<ErinaAnimInstance>();
	animmation->SetOwner(this);


	moveSpeed = 100.0f;
}

Erina::~Erina()
{

}

HRESULT Erina::Init()
{
	Super::Init();
	location = { 350.0f,100.0f };                           
	size = { 20.0f ,32.0f  };
	imageInfo.imageName = L"Erina";
	imageInfo.imageLocation = location;
	imageInfo.atlasInfo.frameSize = { 64.0f,64.0f };
	imageInfo.atlasInfo.frame = {0,0};
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 32.0f,32.0f });
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;

	ID2D1PathGeometry* collsion;
	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&collsion);
	ID2D1GeometrySink* sink = NULL;
	collsion->Open(&sink);

	sink->BeginFigure({0,size.height}, D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F point[3] = {	{size.width,size.height},
								{size.width,0.0f},
								{0.0f,0.0f}};
	sink->AddLines(point,3);
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	sink->Release();

	collisionGeomtry = new GeometryCollision;

	collisionGeomtry->SetCollision(collsion,this);
	//collisionGeomtry;
	geomtryLocation = location;
	

	pikoHammer = CreateObject<Hammer>();
	pikoHammer->SetOwner(this);

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

	playerInput->BindInputKey(VK_UP, KeyInputKinds::StayKey_Down, this, &Erina::MoveUP);
	playerInput->BindInputKey(VK_DOWN, KeyInputKinds::StayKey_Down, this, &Erina::MoveUP);

	playerInput->BindInputKey(VK_LEFT, KeyInputKinds::StayKey_Down, this, &Erina::MoveSide);
	playerInput->BindInputKey(VK_RIGHT, KeyInputKinds::StayKey_Down, this, &Erina::MoveSide);

	playerInput->BindInputKey(ZKey, KeyInputKinds::Key_Down, this, &Erina::AttackPikoHammer);
}

void Erina::MoveUP()
{
	if (moveLock)
		return;
	// 점프가 끝났으면 초기화
	if (((animKinds != AnimmationKinds::Jum) &
		(animKinds != AnimmationKinds::Falling)) & (jumKeyDownTime >= JUM_KEYDOWN_TIME))
		jumKeyDownTime = 0.0f;

	if (KEYMANAGER->GetKeyDown()[VK_UP] & (jumKeyDownTime <= JUM_KEYDOWN_TIME))
	{
		this->isFalling = true;
		animKinds = AnimmationKinds::Jum;
		//location.y -= 12.8f;
		this->geomtryLocation.y -= 9.8f* 0.16f;
		jumKeyDownTime += TIMERMANAGER->GettimeElapsed();
	}
	else if (KEYMANAGER->GetKeyDown()[VK_DOWN])
		this->geomtryLocation.y += moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);
}

void Erina::MoveSide()
{
	if (moveLock)
		return;
	if (KEYMANAGER->GetKeyDown()[VK_LEFT])
	{
		MoveSideValue(moveSpeed * -1.0f);
		if (!isFalling)
			animKinds = AnimmationKinds::Move_Left;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 32.0f,32.0f });
	}
	else if (KEYMANAGER->GetKeyDown()[VK_RIGHT])
	{
		MoveSideValue(moveSpeed * 1.0f);
		if (!isFalling)
			animKinds = AnimmationKinds::Move_Right;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.0f,1.0f }, { 32.0f,32.0f });
	}
}

void Erina::AttackPikoHammer()
{
	if (!moveLock)
	{
		animKinds = AnimmationKinds::Attack1;
		moveLock = true;
	}
	else
	{
		isNextAttack = false;
		switch (animKinds)
		{
		case AnimmationKinds::Attack1:
		case AnimmationKinds::Attack2:
		case AnimmationKinds::Attack3:
			isNextAttack = true;
			break;
		case AnimmationKinds::Attack4:
			isNextAttack = false;
			break;
		}
	}
}
