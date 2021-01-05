#include "Rebbon_Weapon.h"
#include "RebbonAnimInstance.h"

Rebbon_Weapon::Rebbon_Weapon() : 
	isAttack(false)
{
	animmation = CreateObject<RebbonAnimInstance>();
	animmation->SetOwner(this);
}

Rebbon_Weapon::~Rebbon_Weapon()
{
}

HRESULT Rebbon_Weapon::Init()
{
	IMAGEMANAGER->LoadPng(L"Rebbon", L"Chacter/fairy_a");
	imageInfo.imageName = L"Rebbon";
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.atlasInfo.frameSize = { 48.0,48.0f };
	size = { 48.0f  ,48.0f };
	moveSpeed = 1.0f;
	return S_OK;
}

void Rebbon_Weapon::Release()
{
	Super::Release();
}

void Rebbon_Weapon::Update()
{
	Super::Update();
	if (!isAttack)
		MoveToDefaultLocation();
	else
		MoveToAttackLocation();
	imageInfo.imageLocation = location;
}

void Rebbon_Weapon::Render()
{
	Super::Render();
}

void Rebbon_Weapon::Attack()
{
	isAttack = true;
	moveSpeed = 2.0f;
}

void Rebbon_Weapon::MoveToDefaultLocation()
{
	int goalCount = 0;
	Vector2_F ownerLocation;
	if (owner->GetImageInfo_ptr()->affineMatrix.m11 >= 0.0f)
	{
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 24.0f,24.0f });// *Matrix3x2F::Translation(25.f, -10.0f);
		ownerLocation = { owner->GetLocation().x + 25.0f, owner->GetLocation().y - 10.0f };

	}
	else
	{
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.0f,1.0f }, { 24.0f,24.0f });// *Matrix3x2F::Translation(-25.f, -10.0f);
		ownerLocation = { owner->GetLocation().x - 25.0f, owner->GetLocation().y - 10.0f };
	}
	Vector2_F thisLocation = location;
	Vector2_F goalLocation = thisLocation - ownerLocation;

	if ((goalLocation.x < 1.5f) & (goalLocation.x > -1.5f))
	{
		goalLocation.x = 0.0f;
		goalCount++;
	}

	if ((goalLocation.y < 1.5f) & (goalLocation.y > -1.5f))
	{
		goalLocation.y = 0.0f;
		goalCount++;
	}

	if (goalLocation.x > 0)
		location.x -= moveSpeed;
	else if (goalLocation.x < 0)
		location.x += moveSpeed;
	if (goalLocation.y > 0)
		location.y -= moveSpeed;
	else if (goalLocation.y < 0)
		location.y += moveSpeed;
	
	if (goalCount == 2)
	{

	}
}

void Rebbon_Weapon::MoveToAttackLocation()
{
	Vector2_F ownerLocation;
	if (owner->GetImageInfo_ptr()->affineMatrix.m11 >= 0.0f)
	{
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 24.0f,24.0f });// *Matrix3x2F::Translation(25.f, -10.0f);
		ownerLocation = { owner->GetLocation().x - 25.0f, owner->GetLocation().y };

	}
	else
	{
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.0f,1.0f }, { 24.0f,24.0f });// *Matrix3x2F::Translation(-25.f, -10.0f);
		ownerLocation = { owner->GetLocation().x + 25.0f, owner->GetLocation().y};
	}
	Vector2_F thisLocation = location;
	Vector2_F goalLocation = thisLocation - ownerLocation;

	if ((goalLocation.x < 1.5f) & (goalLocation.x > -1.5f))
		goalLocation.x = 0.0f;
	if ((goalLocation.y < 1.5f) & (goalLocation.y > -1.5f))
		goalLocation.y = 0.0f;

	if (goalLocation.x > 0)
		location.x -= moveSpeed;
	else if (goalLocation.x < 0)
		location.x += moveSpeed;
	if (goalLocation.y > 0)
		location.y -= moveSpeed;
	else if (goalLocation.y < 0)
		location.y += moveSpeed;
}
