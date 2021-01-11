#include "Wizard.h"
#include "ImageManager.h"
#include "WizardAnimInstance.h"
#include "WizardAIController.h"
#include "PlayScene.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "Effect.h"
#include "D2DGraphic.h"

Wizard::Wizard() :
	wizardType(WizardType::Blue) , attackTime(0.0f), attackCount(0)
{
	animmation = CreateObject<WizardAnimInstance>();
	animmation->SetOwner(this);

	CreateAIController<WizardAIController>();

	seeAreaSize = { 200.0f,50.0f };
	SettingSeeArea(seeAreaSize);

}

Wizard::~Wizard()
{
}

HRESULT Wizard::Init()
{
	Super::Init();

	location = { 500.0f,200.0f };
	IMAGEMANAGER->LoadPng(L"oldboss3_a", L"Chacter/Enemy/oldboss3_a");
	imageInfo.imageName = L"oldboss3_a";
	imageInfo.atlasInfo.frameSize = { 48.0f,48.0f};
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, {24.0f,24.0f});
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	imageInfo.imageLocation = location;
	size = { 20.0f,50.0f };
	SetGeomtryCollsion();

	return S_OK;
}

void Wizard::Release()
{
	Super::Release();
}

void Wizard::Update()
{
	Super::Update();
	noAnimChange = false;
}

void Wizard::Render()
{
	Super::Render();
#ifdef _DEBUG
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xf0f00f, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																				 location.x + size.width / 2, location.y + size.height / 2 }, brush);
	brush->SetColor(D2D1::ColorF(0x0000ff, 1.0f));
#endif // _DEBUG
}

void Wizard::MoveCharacter(Vector2_F speed)
{
	TimerManager* tiemrManager = TIMERMANAGER;

	if ((animKinds == AnimationKinds::Hit) | (isMoveLock))
		return;
	imageInfo.imageLocation = { location.x ,location.y - 20.0f };

	noAnimChange = true;
	if (speed.x < 0.0f)
	{
		moveSpeed = 50.0f;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.5f,1.5f }, { 24.0f,24.0f });
		animKinds = AnimationKinds::Move_Right;
	}
	else if (speed.x > 0.0f)
	{
		moveSpeed = -50.0f;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, { 24.0f,24.0f });
		animKinds = AnimationKinds::Move_Left;
	}
	else
	{
		if (!isFalling)
		{
			animKinds = AnimationKinds::Idle;
			moveSpeed = 0.0f;
			noAnimChange = false;
		}
	}
	MoveSideValue(moveSpeed);
}

void Wizard::Attack()
{
	attackTime += TIMERMANAGER->GettimeElapsed();
	noAnimChange = true;

	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);

	if ((attackTime >= 0.5f))
	{
		attackTime = 0.0f;
		attackCount++;
		for (int i = 0; i < 10; i++)
		{

			Projectile* projectile = playScene->GetProjectileManager()->SpawnProjectile();
			if (i < 5)
			{
				float angle = 30.0f - (15.0f * (float)(i));
				if (angle <= 0.0f)
					angle -= 360.0f;
				projectile->MoveSetting(DegreeToRadian(angle), { 2.0f,2.0f }, MovePatten::Angle);
			}
			else
				projectile->MoveSetting(DegreeToRadian(210.0f + (15.0f * (float)(i - 5))), { 2.0f,2.0f }, MovePatten::Angle);
			Location spawnLocation;
			if (imageInfo.affineMatrix.m11 > 0 )
				spawnLocation = { worldLocation.x - 18.0f, worldLocation.y - 30.0f };
			else
				spawnLocation = { worldLocation.x + 18.0f, worldLocation.y - 30.0f };
			projectile->SetWorldLocation(spawnLocation);
			projectile->SetGeomtryLocation(spawnLocation);
			projectile->SetIsValid(true);
			projectile->SetOwner(this);
			projectile->SetSize({31.0f, 31.0f});
			ImageInfo* projectileInageinfo = Cast<ImageInfo>(projectile->GetImageInfo_ptr());
			projectileInageinfo->imageEffect = D2DIE_NOIMAGE;
			projectile->CreateEffect();
			projectile->GetEffect()->SetEffect(EffectKinds::Small_Blue_Effect);
		}
	}
	if (attackCount == 5)
	{
		attackCount = 0;
		attackTime = 0.0f;
		isMoveLock = false;
		noAnimChange = false;
		animKinds = AnimationKinds::Idle;
	}
	else
		animKinds = AnimationKinds::Attack1;
}
