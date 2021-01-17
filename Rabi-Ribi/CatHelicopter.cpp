#include "CatHelicopter.h"
#include "CatHelicopterAnimInstance.h"
#include "CatAIController.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "PlayScene.h"
#include "Effect.h"

CatHelicopter::CatHelicopter()
{
	animmation = CreateObject<CatHelicopterAnimInstance>();
	animmation->SetOwner(this);
	CreateAIController<CatAIController>();
	isCanFly = true;
	kinds = CatHelicopterKinds::Pink;
}

CatHelicopter::~CatHelicopter()
{
}

HRESULT CatHelicopter::Init()
{
	Super::Init();
	IMAGEMANAGER->LoadPng(L"effect_a", L"Effect/effect_a");
	imageInfo.imageName = L"effect_a";
	imageInfo.imageEffect = D2DIE_DEFAULT;
	imageInfo.atlasInfo.frameSize = { 31.0f,31.0f };
	imageInfo.imageLocation = { -50.0f,-50.0f };
	moveSpeed = 100.f;
	return S_OK;
}

void CatHelicopter::Update()
{
	Object::Update();

	if ((worldLocation.x == 0.0f) & (worldLocation.y == 0.0f))
		worldLocation = location;
	else
		worldLocation = { geomtryLocation.x + cameraLocation.x , geomtryLocation.y + cameraLocation.y };
	
	cameraLocation = CAMERA->GetLocation();
	location.x = { worldLocation.x - cameraLocation.x };
	location.y = { worldLocation.y - cameraLocation.y };
	geomtryLocation = location;
	imageInfo.imageLocation = location;
	acceleration = 0.0f;
}


void CatHelicopter::MoveCharacter(Vector2_F speed)
{
	TimerManager* tiemrManager = TIMERMANAGER;
	Vector2_F zeroLocation(0.0f,0.0f);
	if (speed == zeroLocation)
		moveSpeed = 0.0f;

	if ((animKinds == AnimationKinds::Hit) | (isMoveLock))
		return;
	if ((speed.x <= 10.0f) & (speed.x >= -10.0f))
		moveSpeed = 0.0f;
	else
	{
		if (speed.x < 0)
			moveSpeed = +120.0f;
		else
			moveSpeed = -120.0f;
	}
	MoveSideValue(moveSpeed);
	if ((speed.y <= 10.0f) & (speed.y >= -10.0f))
		moveSpeed = 0.0f;
	else
	{
		if (speed.y < 0)
			moveSpeed = +120.0f;
		else
			moveSpeed = -120.0f;
	}
	MoveUpValue(moveSpeed);

}

void CatHelicopter::NomalAttack(float ratio)
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		ProjectileManager* projectileManager = playScene->GetProjectileManager();
		Projectile* projectile; 
		Vector2_F speed = { 3.0f * ratio,3.0f *ratio };

		for (int i = 0; i < 18; i++)
		{
			projectile = projectileManager->SpawnProjectile();
			projectile->SetIsValid(true);
			ImageInfo* projectileImageinfo = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
			projectileImageinfo->imageEffect = D2DIE_NOIMAGE;
			//projectileImageinfo->imageName = L"effect_a";
			//projectileImageinfo->atlasInfo.frameSize = { 31.0f,31.0f };
			//projectileImageinfo->atlasInfo.frame = {25,1};
			//projectileImageinfo->affineMatrix = Matrix3x2F::Scale({ 0.8f,0.8f }, {15.5f,15.5f }) *
			//	Matrix3x2F::Rotation((i * 20.0f), { projectileImageinfo->atlasInfo.frameSize.width / 2.0f , projectileImageinfo->atlasInfo.frameSize.height / 2.0f });
			projectileImageinfo->exposureEffectInfo = 1.0f;
			projectile->MoveSetting(DegreeToRadian(i * 20.0f), speed, MovePatten::Angle);
			projectile->SetWorldLocation(worldLocation);
			projectile->SetGeomtryLocation(worldLocation);
			projectile->SetOwner(Cast<Actor>(GetParentsObject()));
			projectile->CreateEffect();
			projectile->GetEffect()->SetOwner(projectile);
			projectile->GetEffect()->SetEffect(EffectKinds::Blue_Projectlie);
		}
	}
}

void CatHelicopter::TunMoveAttack()
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		ProjectileManager* projectileManager = playScene->GetProjectileManager();
		Projectile* projectile;
		Vector2_F speed = { 3.0f ,3.0f  };

		for (int i = 0; i < 10; i++)
		{
			projectile = projectileManager->SpawnProjectile();
			projectile->SetIsValid(true);
			ImageInfo* projectileImageinfo = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
			//projectileImageinfo->imageName = L"effect_a";
			//projectileImageinfo->atlasInfo.frameSize = { 31.0f,31.0f };
			//projectileImageinfo->atlasInfo.frame = { 24,1 };
			//projectileImageinfo->affineMatrix = Matrix3x2F::Scale({ 1.8f,1.0f }, { 15.5f,15.5f }) *
			//	Matrix3x2F::Rotation((i * 36.0f), { projectileImageinfo->atlasInfo.frameSize.width / 2.0f , projectileImageinfo->atlasInfo.frameSize.height / 2.0f });
			//projectileImageinfo->exposureEffectInfo = 1.0f;
			projectileImageinfo->imageEffect = D2DIE_NOIMAGE;
			projectile->MoveSetting(DegreeToRadian(i * 36.0f), speed, MovePatten::AngleTun);
			projectile->SetWorldLocation(worldLocation);
			projectile->SetGeomtryLocation(worldLocation);
			projectile->SetOwner(Cast<Actor>(GetParentsObject()));
			projectile->SetProjectileAnimationKinds(ProjectileAnimationKinds::None);
			projectile->CreateEffect();
			projectile->GetEffect()->SetOwner(projectile);
			projectile->GetEffect()->SetEffect(EffectKinds::Red_Projectlie);
		}
	}
}

void CatHelicopter::TunMove_8Attack()
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		ProjectileManager* projectileManager = playScene->GetProjectileManager();
		Projectile* projectile;
		Vector2_F speed = { 3.0f ,3.0f };

		for (int i = 0; i < 10; i++)
		{
			projectile = projectileManager->SpawnProjectile();
			projectile->SetIsValid(true);
			ImageInfo* projectileImageinfo = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
			//projectileImageinfo->imageName = L"effect_a";
			//projectileImageinfo->atlasInfo.frameSize = { 31.0f,31.0f };
			//projectileImageinfo->atlasInfo.frame = { 24,1 };
			//projectileImageinfo->affineMatrix = Matrix3x2F::Scale({ 1.8f,1.0f }, { 15.5f,15.5f }) *
			//	Matrix3x2F::Rotation((i * 36.0f), { projectileImageinfo->atlasInfo.frameSize.width / 2.0f , projectileImageinfo->atlasInfo.frameSize.height / 2.0f });
			//projectileImageinfo->exposureEffectInfo = 1.0f;
			projectileImageinfo->imageEffect = D2DIE_NOIMAGE;
			float angle = (-30.0f + ((360.0f / 5.0f) * (i /2))) + (15.0f * (i % 2 ));
			projectile->MoveSetting(DegreeToRadian(angle), speed, MovePatten::AngleTunAngle);
			projectile->SetaddAngle(DegreeToRadian(15.0f) * powf(-1.0f, (i % 2) + 1.0f));
			projectile->SetWorldLocation(worldLocation);
			projectile->SetGeomtryLocation(worldLocation);
			projectile->SetOwner(Cast<Actor>(GetParentsObject()));
			projectile->SetProjectileAnimationKinds(ProjectileAnimationKinds::None);
			projectile->CreateEffect();
			projectile->GetEffect()->SetOwner(projectile);
			projectile->GetEffect()->SetEffect(EffectKinds::Red_Projectlie);
		}
	}
}

void CatHelicopter::TagetAttack()
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		ProjectileManager* projectileManager = playScene->GetProjectileManager();
		Projectile* projectile;
		Vector2_F speed = { 3.0f ,5.0f };
		{
			projectile = projectileManager->SpawnProjectile();
			projectile->SetIsValid(true);
			ImageInfo* projectileImageinfo = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
			projectileImageinfo->imageEffect = D2DIE_NOIMAGE;
			projectile->MoveSetting(DegreeToRadian(90.0f), speed, MovePatten::Angle);
			projectile->SetWorldLocation(worldLocation);
			projectile->SetGeomtryLocation(worldLocation);
			projectile->SetOwner(Cast<Actor>(GetParentsObject()));
			projectile->SetProjectileAnimationKinds(ProjectileAnimationKinds::None);
			projectile->CreateEffect();
			projectile->GetEffect()->SetOwner(projectile);
			projectile->GetEffect()->SetEffect(EffectKinds::Flashing_Rotation_Effect);
			projectile->GetEffect()->SetEffectFrame(EffectBody::EffectFrame::Blue_EllipseProjectlie_Frame);
		}
	}
}

void CatHelicopter::TagetMove()
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		Vector2_F playerLocation = playScene->GetPlayer()->GetWorldLocation();
		AIController->MoveToLocation({ playerLocation.x ,location.y });

	}
}
