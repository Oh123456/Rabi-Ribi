#include "PlayScene.h"
#include "TileMap.h"
#include "D2DGraphic.h"
#include "Erina.h"
#include "GeometryCollision.h"
#include "CollisionManager.h"
#include "PlayerInput.h"
#include "Rabbit.h"
#include "Wizard.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Effect.h"


PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

HRESULT PlayScene::Init()
{
	test =CreateObject<TileMap>();
	test->LoadTile("Save/CameTest.map");
	CollisionManager* collision = CreateObject<CollisionManager>(true);
	player = CreateObject<Erina>();
	CreateObject<Rabbit>();
	CreateObject<Wizard>();
	IMAGEMANAGER->LoadPng(L"테스트배경",L"forest3_a");
	IMAGEMANAGER->LoadPng(L"Erina", L"Chacter/player_a");

	testbg.imageName = L"테스트배경";
	testbg.imageLocation = { 0.0f,0.0f };
	testbg.scaleInfo.scaleSize = { 3.0f,3.0f };
	testbg.imageEffect = D2DIE_SCALE;
	CAMERA->SetZoom({ 2.0f,2.2f });
	//D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({ 2.0f,2.2f }));
	Cast<Character>(player)->PlayerInputSetting(CreateObject<PlayerInput>(false));
	projectileManager = CreateObject<ProjectileManager>();
	collision->SettingActor(this);

	IEffect* test123 = CreateObject<Effect>();
	test123->SetSocketLocation({ 300.0f,300.f });
	test123->SetEffect(EffectKinds::Small_Blue_Effect);


	CAMERA->SetFocusActor(player);
	return S_OK;
}

void PlayScene::Release()
{
	Super::Release();
	D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({ 1.0f,1.0f }));
}

void PlayScene::Update()
{
	Super::Update();
}



void GetGeomrtyPoint(ID2D1PathGeometry* const geometry, const GeometryInfo & geomrtyinfo, D2D_RECT_F rect)
 {

	ID2D1GeometrySink* sink = NULL;

	HRESULT s = geometry->Open(&sink);
	if (sink == nullptr)
		return;
	D2D1_POINT_2F start;
	Matrix3x2F matrix = Matrix3x2F::Rotation(geomrtyinfo.rotation, { rect.left + (rect.right - (rect.left)) / 2,rect.top + (rect.right - (rect.left)) / 2 });
	if (geomrtyinfo.isRevers)
		matrix = matrix * Matrix3x2F::Scale({ -1.0f,1.0f }, { (float)rect.left + 16.0f, (float)rect.top + 16.0f });
	switch (geomrtyinfo.geometrykind)
	{
	case GeometryKinds::Triangle:
	{
		start = D2D1::Point2F(rect.left, rect.bottom);
		start = matrix.TransformPoint(start);
		sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[2] = { rect.left + geomrtyinfo.width ,rect.bottom ,
											rect.left  ,rect.bottom - geomrtyinfo.height };
		point[0] = matrix.TransformPoint(point[0]);
		point[1] = matrix.TransformPoint(point[1]);
		sink->AddLines(point, 2);
		// 피겨의 끝.
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		break;
	}
	case GeometryKinds::Square:
	{
		start = matrix.TransformPoint({ rect.left, rect.bottom });
		sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[3] = { {rect.left + geomrtyinfo.width,rect.bottom},
									{rect.left + geomrtyinfo.width,rect.bottom - geomrtyinfo.height},
									{rect.left ,rect.bottom - geomrtyinfo.height} };
		point[0] = matrix.TransformPoint(point[0]);
		point[1] = matrix.TransformPoint(point[1]);
		point[2] = matrix.TransformPoint(point[2]);
		sink->AddLines(point, 3);
		// 피겨의 끝.
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	}
	break;
	case GeometryKinds::Trapezoid:
	{


		start = matrix.TransformPoint({ rect.left, rect.bottom });
		sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[4] = { rect.left, rect.bottom - (geomrtyinfo.height + geomrtyinfo._height),
											{rect.left + geomrtyinfo.width,rect.bottom - geomrtyinfo.height},
											{rect.left + geomrtyinfo.width,rect.bottom},
											{rect.left ,rect.bottom} };
		point[0] = matrix.TransformPoint(point[0]);
		point[1] = matrix.TransformPoint(point[1]);
		point[2] = matrix.TransformPoint(point[2]);
		point[3] = matrix.TransformPoint(point[3]);
		sink->AddLines(point, 4);
		// 피겨의 끝.
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		break;
	}
	default:
		break;
	}

	sink->Close();
	sink->Release();


}


void PlayScene::Render()
{
	IMAGEMANAGER->ImageRander(testbg);
	Super::Render();
	static float a = 1.0f;
	const Location& playerLocation = player->GetLocation();
	const SIZE_F& playerSize = player->GetSize();
	D2D_POINT_2F playrLT = { (playerLocation.x - (playerSize.width / 2)) ,(playerLocation.y - (playerSize.height / 2)) };
	//D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ playrLT.x,playrLT.y,playrLT.x + (playerSize.width ),playrLT.y + (playerSize.height) }, D2D::GetSingleton()->GetBrush());

	//list<GeometryCollision*> collisionlist = test->GetcollisionList();
	//list<GeometryCollision*>::const_iterator c_it;
	//GeometryCollision* tileCollision = nullptr;
	//for (c_it = collisionlist.begin(); c_it != collisionlist.end(); c_it++)
	//{
	//	tileCollision = (*c_it);
	//	if (tileCollision == nullptr)
	//		continue;
	//	const Location& Location = tileCollision->GetOwnerLocation();
	//	//D2D::GetSingleton()->GetD2DRenderTarget()->DrawGeometry(tileCollision->geometry, D2D::GetSingleton()->GetBrush());
	//	if (tileCollision->info.geometrykind != GeometryKinds::Trapezoid)
	//		continue;
	//	ID2D1PathGeometry* test;
	//	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&test);
	//	
	//	GetGeomrtyPoint(test, tileCollision->info, RectF(Location.x, Location.y, Location.x + 32.0f, Location.y + 32.0f));
	//	D2D::GetSingleton()->GetD2DRenderTarget()->FillGeometry(test, D2D::GetSingleton()->GetBrush());
	//	test->Release();
	//}

}
