#include "Rebbon_Weapon.h"
#include "RebbonAnimInstance.h"
#include "PlayScene.h"
#include "ProjectileManager.h"
#include "Projectile.h"

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
	moveSpeed = 100.0f;
	chargeTiem = 0.0f;
	isAttackend = false;
	return S_OK;
}

void Rebbon_Weapon::Release()
{
	Super::Release();
}

void Rebbon_Weapon::Update()
{
	Super::Update();

	//location = geomtryLocation;

}

void Rebbon_Weapon::Render()
{
	Super::Render();
}

void Rebbon_Weapon::Attack()
{
	isAttack = true;
	isAttackend = false;
	isChargeAttack = false;
	moveSpeed = 300.0f;
}

void Rebbon_Weapon::ChargeAttack()
{
	chargeTiem += TIMERMANAGER->GettimeElapsed();
}

void Rebbon_Weapon::ChargeAttackFire()
{
	if (chargeTiem > 1.0f)
	{
		isChargeAttack = true;
		isAttackend = false;
		moveSpeed = 1000.f;
	}
	chargeTiem = 0.0f;
}


void Rebbon_Weapon::MoveToDefaultLocation()
{
	Vector2_F ownerLocation;
	if (owner->GetImageInfo_ptr()->affineMatrix.m11 >= 0.0f)
	{
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 24.0f,24.0f });// *Matrix3x2F::Translation(25.f, -10.0f);
		ownerLocation = { owner->GetLocation().x + 40.0f, owner->GetLocation().y - 15.0f };

	}
	else
	{
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.0f,1.0f }, { 24.0f,24.0f });// *Matrix3x2F::Translation(-25.f, -10.0f);
		ownerLocation = { owner->GetLocation().x - 40.0f, owner->GetLocation().y - 15.0f };
	}
	Vector2_F thisLocation = location;
	Vector2_F goalLocation = thisLocation - ownerLocation;

	if ((goalLocation.x < 10.5f) & (goalLocation.x > -1.5f))
	{
		moveSpeed = 100.0f;
		goalLocation.x = 0.0f;
	}
	if ((goalLocation.y < 10.5f) & (goalLocation.y > -10.5f))
	{
		//moveSpeed = 1.0f;
		goalLocation.y = 0.0f;
	}
	if (goalLocation.x > 0)
		location.x -= moveSpeed * TIMERMANAGER->GettimeElapsed();
	else if (goalLocation.x < 0)
		location.x += moveSpeed * TIMERMANAGER->GettimeElapsed();
	if (goalLocation.y > 0)
		location.y -= moveSpeed * TIMERMANAGER->GettimeElapsed();
	else if (goalLocation.y < 0)
		location.y += moveSpeed * TIMERMANAGER->GettimeElapsed();
	

}

void Rebbon_Weapon::MoveToAttackLocation()
{
	int goalCount = 0;
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
		location.x -= moveSpeed * TIMERMANAGER->GettimeElapsed();
	else if (goalLocation.x < 0)
		location.x += moveSpeed * TIMERMANAGER->GettimeElapsed();
	if (goalLocation.y > 0)
		location.y -= moveSpeed * TIMERMANAGER->GettimeElapsed();
	else if (goalLocation.y < 0)
		location.y += moveSpeed * TIMERMANAGER->GettimeElapsed();


	if (goalCount == 2)
	{
		if (!isAttackend)
			OnFire();
	}
}

void Rebbon_Weapon::OnFire()
{
	ProjectileManager* projectileManager = Cast<PlayScene>(SceneManager::currScene)->GetProjectileManager();
	const list <class Projectile*>& list = projectileManager->GetProjectile();
	Projectile* projectile = projectileManager->SpawnProjectile();
	ImageInfo* projectileImage = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
	Vector2_F speed;
	MovePatten movePatten;
	float angle = 0.0f;
	D2D1_SIZE_F scaleValue = {1.0f,1.0f};
	switch (kinds)
	{
	case Rebbon_WeaponKinds::Nomal:
		if (owner->GetImageInfo_ptr()->affineMatrix.m11 >= 0.0f)
			speed = { -7.0f,0.0f };
		else
			speed = { 7.0f,0.0f };
		movePatten = MovePatten::Nomal;
		scaleValue = { 1.0f,1.0f };
		if (isChargeAttack)
		{
			projectile->SetProjectileAnimationKinds(ProjectileAnimationKinds::Circle_Blue);
			scaleValue = { 1.5f,1.5f };
			isChargeAttack = false;
		}
		else
			projectile->SetProjectileAnimationKinds(ProjectileAnimationKinds::Circle_Red);
		break;
	default:
		break;
	}
	projectileImage->affineMatrix = Matrix3x2F::Scale(scaleValue,
		{ projectileImage->atlasInfo.frameSize.width / 2.0f ,projectileImage->atlasInfo.frameSize.height / 2.0f });
	if (owner->GetImageInfo_ptr()->affineMatrix.m11 >= 0.0f)
	{
		if (projectileImage->affineMatrix.m11 > 0.0f)
			projectileImage->affineMatrix.m11 *= -1.0f;
	}
	else
	{
		if (projectileImage->affineMatrix.m11 < 0.0f)
			projectileImage->affineMatrix.m11 *= -1.0f;
	}
	projectile->MoveSetting(angle, speed, movePatten);
	projectile->SetLocation({ worldLocation.x + 25.0f,worldLocation.y });
	projectile->SetGeomtryLocation({ worldLocation.x + 25.0f,worldLocation.y });
	projectile->SetIsValid(true);
	projectile->SetOwner(owner);
	TIMERMANAGER->SetTimer(attackEndTimer,this,&Rebbon_Weapon::AttackEndTimer, 0.5f);
	isAttackend = true;
	moveSpeed = 300.0f;
}

void Rebbon_Weapon::AttackEndTimer()
{
	if (chargeTiem == 0.0f)
	{
		isAttack = false;
		//isAttackend = false;
		TIMERMANAGER->DeleteTimer(attackEndTimer);
	}
}

void Rebbon_Weapon::MoveMent()
{
	if (!isAttack & !isChargeAttack)
		MoveToDefaultLocation();
	else
		MoveToAttackLocation();
}
