#include "Enemy.h"
#include "GeometryCollision.h"
#include "PlayScene.h"
#include "EnemyAIController.h"
#include "D2DGraphic.h"

Enemy::Enemy()
{
	actorType = ActorType::Enemy;
	invincibleTime = 0.5f;

	onSee.BindObject(this,&Enemy::See);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Super::Update();
}

void Enemy::MoveCharacter()
{
	location = geomtryLocation;
	worldLocation = { geomtryLocation.x + cameraLocation.x, geomtryLocation.y + cameraLocation.y };
}

void Enemy::Render()
{
	Super::Render();
#ifdef _DEBUG

	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xf0f00f, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																location.x + size.width / 2, location.y + size.height / 2 }, brush);
	if (seeArea)
	{

		brush->SetColor(D2D1::ColorF(0x0000ff, 1.0f));

		brush = D2D::GetSingleton()->GetBrush();
		brush->SetColor(D2D1::ColorF(0xff23ff, 1.0f));
		D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(seeArea->GetGeometryRect(), brush);
	}
#endif // _DEBUG

}

void Enemy::MoveCharacter(Vector2_F speed)
{
}

void Enemy::SettingSeeArea()
{
	SettingSeeArea(seeAreaSize);
}

void Enemy::SettingSeeArea(SIZE_F& size)
{
	ID2D1PathGeometry* collsion;
	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&collsion);
	ID2D1GeometrySink* sink = NULL;
	collsion->Open(&sink);

	sink->BeginFigure({ 0,size.height }, D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F point[3] = { {size.width,size.height},
								{size.width,0.0f},
								{0.0f,0.0f} };
	sink->AddLines(point, 3);
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	sink->Release();
	seeAreaSize = size;

	seeArea = new GeometryCollision;

	seeArea->SetCollision(collsion, seeAreaSize , this);
}

void Enemy::HitCharacterInvincible(Character* hitCharacter)
{
	hitCharacter->SetInvincibleTimer();
}

void Enemy::See(Object * object)
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		if ((object != this) & (object == playScene->GetPlayer()))
		{
			EnemyAIController* eAIController = Cast<EnemyAIController>(AIController);
			eAIController->SetTaget(Cast<Actor>(object));
			isSee = true;
		}
	}
}
