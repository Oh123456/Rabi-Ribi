#include "Erina.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"
#include "PlayerInput.h"
#include "ErinaAnimInstance.h"

Erina::Erina()
{
	animmation = CreateObject<ErinaAnimInstance>();
	animmation->SetOwner(this);
}

Erina::~Erina()
{

}

HRESULT Erina::Init()
{
	location = { 350.0f,200.0f };                           
	size = { 20.0f,32.0f };
	imageInfo.imageName = L"Erina";
	imageInfo.imageLocation = location;
	imageInfo.atlasInfo.frameSize = { 64.0f,64.0f };
	imageInfo.atlasInfo.frame = {0,0};
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


	moveSpeed = 1.0f;
	return S_OK;
}

void Erina::Release()
{
	Super::Release();
	SAFE_RELEASE(collisionGeomtry)
}

void Erina::Update()
{
	Super::Update();
	//
	geomtryLocation = location;
	if (isFalling)
	{
		acceleration = 0.98f*(TIMERMANAGER->GettimeElapsed() * 100.0f);
		geomtryLocation.y += acceleration;
	}
	else
	{
		acceleration = 0.0f;
		animKinds = ErinaAnimmationKinds::Idle;
	}
	imageInfo.imageLocation = location;
}

void Erina::Render()
{
	Super::Render();
	//IMAGEMANAGER->ImageRander(imageInfo);
}

void Erina::PlayerInputSetting(PlayerInput* playerInput)
{
	Super::PlayerInputSetting(playerInput);

	playerInput->BindInputKey(VK_UP, KeyInputKinds::StayKey_Down, this, &Erina::MoveUP);
	playerInput->BindInputKey(VK_DOWN, KeyInputKinds::StayKey_Down, this, &Erina::MoveUP);

	playerInput->BindInputKey(VK_LEFT, KeyInputKinds::StayKey_Down, this, &Erina::MoveSide);
	playerInput->BindInputKey(VK_RIGHT, KeyInputKinds::StayKey_Down, this, &Erina::MoveSide);
}

void Erina::MoveUP()
{
	if (KEYMANAGER->GetKeyDown()[VK_UP])
	{
		this->isFalling = true;
		//location.y -= 12.8f;
		this->geomtryLocation.y -= 12.8f* (TIMERMANAGER->GettimeElapsed() * 100.0f);
	}
	else if (KEYMANAGER->GetKeyDown()[VK_DOWN])
		this->geomtryLocation.y += moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);
}

void Erina::MoveSide()
{
	if (KEYMANAGER->GetKeyDown()[VK_LEFT])
	{
		this->geomtryLocation.x -= moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);
		animKinds = ErinaAnimmationKinds::Move_Left;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 32.0f,32.0f });
	}
	else if (KEYMANAGER->GetKeyDown()[VK_RIGHT])
	{
		this->geomtryLocation.x += moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);
		animKinds = ErinaAnimmationKinds::Move_Right;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.0f,1.0f }, { 32.0f,32.0f });
	}
}
