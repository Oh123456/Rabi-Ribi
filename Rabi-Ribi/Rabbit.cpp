#include "Rabbit.h"
#include "RabbitAnimInstance.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"
#include "EnemyAIController.h"
#include "PlayScene.h"

Rabbit::Rabbit() : 
	jumTimerCount(0)
{
	animmation = CreateObject<RabbitAnimInstance>();
	animmation->SetOwner(this);

	seeAreaSize = { 200.0f,20.0f };
	SettingSeeArea(seeAreaSize);
	moveSpeed = 0.11f;

	CreateAIController<EnemyAIController>();

	//onSee.BindObject(this,&Rabbit::OnSee);
	onHit.BindObject(this,&Rabbit::OnHit);
}

Rabbit::~Rabbit()
{
}

HRESULT Rabbit::Init()
{
	Super::Init();
	IMAGEMANAGER->LoadPng(L"enemy1",L"Chacter/Enemy/enemy1_a");
	location = { 350.0f,200.0f };
	worldLocation = location;
	size = { 20.0f * 1.5f,20.0f * 1.5f};
	hitBoxSize = size;
	imageInfo.imageName = L"enemy1";
	imageInfo.imageLocation = { location.x ,location.y - 20.0f };
	imageInfo.atlasInfo.frameSize = { 48.0f,48.0f };
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, { 48.0f,48.0f });
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	hp = 100;
	damage = 10;

	SetGeomtryCollsion();

	return S_OK;
}

void Rabbit::Release()
{
	Super::Release();
}

void Rabbit::Update()
{
	Super::Update();
	imageInfo.imageLocation = { location.x ,location.y - 15.0f };
	//if (!isMoveLock)
	//	geomtryLocation.x += moveSpeed;
	noAnimChange = true;
}

void Rabbit::Render()
{
	Super::Render();
#ifdef _DEBUG
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xf0f00f, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																				 location.x + size.width / 2, location.y + size.height / 2 } , brush);
	brush->SetColor(D2D1::ColorF(0x0000ff, 1.0f));
#endif // _DEBUG
}

void Rabbit::MoveCharacter(Vector2_F speed)
{
	TimerManager* tiemrManager = TIMERMANAGER;
	
	if (animKinds == AnimationKinds::Hit)
		return;
	imageInfo.imageLocation = { location.x ,location.y - 20.0f };
	
	if (speed.x < 0.0f)
	{
		moveSpeed = 50.0f;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.5f,1.5f }, { 24.0f,24.0f });
		animKinds = AnimationKinds::Move_Right;
		if ((!isFalling) & (!tiemrManager->ExistTimer(jumTimer)))
			tiemrManager->SetTimer(jumTimer, this, &Rabbit::Jum, 0.1f);
	}
	else if (speed.x > 0.0f)
	{
		moveSpeed = -50.0f;
		imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, { 24.0f,24.0f });
		animKinds = AnimationKinds::Move_Left;
		if ((!isFalling) & (!tiemrManager->ExistTimer(jumTimer)))
			tiemrManager->SetTimer(jumTimer, this, &Rabbit::Jum, 0.1f);
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

void Rabbit::OnSee(Object* object)
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		if ((object != this) & (object == playScene->GetPlayer()))
		{
			EnemyAIController* eAIController = Cast<EnemyAIController>(AIController);
			eAIController->SetTaget(Cast<Actor>(object));
		}
	}
}

void Rabbit::OnHit(Object* object)
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		if ((object != this) & (object == playScene->GetPlayer()))
		{
			Character* player = Cast<Character>(object);
			player->TakeDamage(damage);
		}
	}
}

void Rabbit::Jum()
{
	TimerManager* tiemrManager = TIMERMANAGER;
	jumTimerCount++;
	acceleration = (-98.0f * tiemrManager->GetTimeElapsed() * 1.8f);
	if (jumTimerCount >= 3)
	{
		jumTimerCount = 0;
		tiemrManager->DeleteTimer(jumTimer);
	}
}
