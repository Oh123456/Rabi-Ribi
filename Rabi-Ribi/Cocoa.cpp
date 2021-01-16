#include "Cocoa.h"
#include "CocoaAnimInstance.h"
#include "CocoaAIController.h"
#include "PlayScene.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "CatHelicopter.h"
#include "AIBase.h"

Cocoa::Cocoa()
{
	cat[0] = nullptr;
	cat[1] = nullptr;
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
	hp = 2000;
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
	for (int i = 0; i < 2; i++)
	{
		if (cat[i])
		{
			if ((cat[i]->GetWorldLocation().x < -30.0f) | (cat[i]->GetWorldLocation().y < -30.0f))
			{
				DeleteChild(cat[i]);
				cat[i] = nullptr;
			}
		}
	}
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

void Cocoa::TakeDamage(int damage)
{
	Super::TakeDamage(damage);
	isMoveLock = false;
}

void Cocoa::SetBackJumpShot()
{
	onBackJumpShot.BindObject(this, &Cocoa::JumpShot);
}

void Cocoa::BoomAttack()
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		ProjectileManager* projectileManager = playScene->GetProjectileManager();
		Projectile** blackBomb = projectileManager->SpawnBlackBomb();
		if (blackBomb == nullptr)
			return;
		Vector2_F bombSpeed;
		if (imageInfo.affineMatrix.m11 > 0.0f)
			bombSpeed = { -3.0f,-3.0f };
		else
			bombSpeed = { 3.0f,-3.0f };

		blackBomb[0]->SetIsValid(true);
		blackBomb[0]->Init();
		blackBomb[0]->SetWorldLocation(worldLocation);
		blackBomb[0]->SetSpeed(bombSpeed);


		bombSpeed.x *= 1.5f;
		blackBomb[1]->SetIsValid(true);
		blackBomb[1]->Init();
		blackBomb[1]->SetWorldLocation(worldLocation);
		blackBomb[1]->SetSpeed(bombSpeed);
	}
}

void Cocoa::CallCatHelicoter()
{
	if (cat[0])
	{
		DeleteChild(cat[0]);
		cat[0] = nullptr;
	}
	cat[0] = CreateObject<CatHelicopter>();
	cat[0]->SetWorldLocation(worldLocation);
	cat[0]->SetGeomtryLocation(worldLocation);
	cat[0]->SetCatHelicopterKinds(CatHelicopterKinds::Yellow);
	AIBase* ai = Cast<AIBase>(cat[0]->GetAIController());
	ai->MoveToLocation({ worldLocation.x , worldLocation.y - 200.0f});
}

void Cocoa::CallTwoCatHelicoter()
{
	for (int i = 0; i < 2; i++)
	{
		if (cat[i])
		{
			DeleteChild(cat[i]);
			cat[i] = nullptr;
		}
		cat[i] = CreateObject<CatHelicopter>();
		cat[i]->SetWorldLocation({ (worldLocation.x - (20.f*i)), worldLocation.y - (20.f*i)});
		cat[i]->SetGeomtryLocation({ worldLocation.x - (20.f*i), worldLocation.y - (20.f*i) });
		AIBase* ai = Cast<AIBase>(cat[i]->GetAIController());
		ai->MoveToLocation({ worldLocation.x - (20.f*i), worldLocation.y - 200.0f - (20.f*i) });
	}
}

Vector2_F Cocoa::MoveFont()
{
	if (imageInfo.affineMatrix.m11 > 0.0f)
		return { worldLocation.x - 50.f,worldLocation.y };
	else
		return { worldLocation.x + 50.f,worldLocation.y };
}


void Cocoa::JumpShot()
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		ProjectileManager* projectileManager = playScene->GetProjectileManager();
		Projectile* projectile;
		Vector2_F speed = {5.0f,5.0f};
		float standardAngle = 165.0f;
		float moveBack = 0.0f;
		if (imageInfo.affineMatrix.m11 > 0.0f)
		{
			standardAngle = 165.0f;
			moveBack += 5.0f;
		}
		else
		{
			standardAngle = 75.0f;
			moveBack -= 5.0f;
		}
		for (int i = 0; i < 4; i++)
		{
			projectile = projectileManager->SpawnProjectile();
			projectile->SetIsValid(true);
			float angle = standardAngle - (i * 15.0f);
			ImageInfo* projectileImageinfo = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
			projectileImageinfo->affineMatrix = projectileImageinfo->affineMatrix *
				Matrix3x2F::Rotation(angle, { projectileImageinfo->atlasInfo.frameSize.width / 2.0f , projectileImageinfo->atlasInfo.frameSize.height / 2.0f });
			AddImageEffect(*projectileImageinfo, D2DIE_EXPOSUREEFFECT);
			projectileImageinfo->exposureEffectInfo = 1.0f;
			projectile->MoveSetting(DegreeToRadian(angle), speed, MovePatten::Angle);
			projectile->SetProjectileAnimationKinds(ProjectileAnimationKinds::Circle_Red);
			projectile->SetWorldLocation(worldLocation);
			projectile->SetGeomtryLocation(worldLocation);
			projectile->SetOwner(this);
		}
		acceleration -= 3.5f;
		MoveSideValue(moveBack);
	}
	onBackJumpShot.UnBind();
}
