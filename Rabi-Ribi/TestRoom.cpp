#include "TestRoom.h"
#include "TileMap.h"
#include "D2DGraphic.h"
#include "Erina.h"
#include "GeometryCollision.h"
#include "CollisionManager.h"


TestRoom::TestRoom()
{
}

TestRoom::~TestRoom()
{
}

HRESULT TestRoom::Init()
{
	test =CreateObject<TileMap>();
	test->LoadTile("Save/Test2.map");
	player = CreateObject<Erina>();
	IMAGEMANAGER->LoadPng(L"테스트배경",L"forest3_a");
	IMAGEMANAGER->LoadPng(L"Erina", L"Chacter/player_a");

	testbg.imageName = L"테스트배경";
	testbg.imageLocation = { 0.0f,0.0f };
	testbg.scaleInfo.scaleSize = { 3.0f,3.0f };
	testbg.imageEffect = D2DIE_SCALE;
	D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({ 2.0f,2.2f }));

	CreateObject<CollisionManager>(false)->SettingActor(this);

	return S_OK;
}

void TestRoom::Release()
{
	Super::Release();
}

void TestRoom::Update()
{
	Super::Update();

	//map<CollisionIndexInfo, GeometryCollision*> collisionlist = test->GetcollisionList();
	//map<CollisionIndexInfo, GeometryCollision*>::const_iterator c_it;
	//if (collisionlist.empty())
	//	return;

	//ID2D1PathGeometry* playerCollision = const_cast<ID2D1PathGeometry*>(player->GetCollisionGeomtry());
	//const Location& playerLocation = player->GetLocation();
	//const SIZE_F& playerSize = player->GetSize();

	//// 플레이어의 LT;
	//D2D_POINT_2F playrLT = { (playerLocation.x - (playerSize.width/2)) ,(playerLocation.y - (playerSize.height/2)) };
	//GeometryCollision* tileCollision = nullptr;
	//Character* cplayer = Cast<Character>(player);
	////cplayer->SetFalling(true);
	//bool ishit = false;
	//Index_2U playerindex[4];// playerLocation.x;
	//int LT_x = (int)playrLT.x / 32 ;
	//int LT_y = (int)playrLT.y / 32;
	//playerindex[0] = { LT_x , LT_y };
	//playerindex[1] = { LT_x + 1 , LT_y };
	//playerindex[2] = { LT_x , LT_y + 1};
	//playerindex[3] = { LT_x + 1, LT_y + 1};

	//// 상 4 좌우22 하 4
	//GeometryCollision* topCollosion[4];
	//GeometryCollision* SideCollosion[4];
	//GeometryCollision* battomCollosion[4];

	//c_it = collisionlist.begin();
	//if (c_it == collisionlist.end())
	//	return;
	//CollisionIndexInfo begin = c_it->first;
	//UINT tileX_Size = begin.tileX_Size;

	//CollisionIndexInfo find;
	//find.index = (LT_x - 1) + (LT_y + 2) * tileX_Size;
	//c_it = collisionlist.find(find);
	//battomCollosion[0] = nullptr;
	//if (c_it != collisionlist.end())
	//	battomCollosion[0] = c_it->second;

	//find.index = (LT_x) + (LT_y + 2) * tileX_Size;
	//c_it = collisionlist.find(find);
	//battomCollosion[1] = nullptr;
	//if (c_it != collisionlist.end())
	//	battomCollosion[1] = c_it->second;


	//find.index = (LT_x + 1) + (LT_y + 2) * tileX_Size;
	//c_it = collisionlist.find(find);
	//battomCollosion[2] = nullptr;
	//if (c_it != collisionlist.end())
	//	battomCollosion[2] = c_it->second;


	//find.index = (LT_x + 2) + (LT_y + 2) * tileX_Size;
	//c_it = collisionlist.find(find);
	//battomCollosion[3] = nullptr;
	//if (c_it != collisionlist.end())
	//	battomCollosion[3] = c_it->second;

	//cplayer->SetFalling(true);
	//for (int i = 0; i < 4; i++)
	//{
	//	if (battomCollosion[i])
	//	{
	//		if (battomCollosion[i]->CollisionHitCheck(playerCollision, playrLT))
	//		{
	//			cplayer->SetFalling(false);
	//			
	//		}
	//	}
	//}

	//cplayer->MoveCharacter();
	//collisionlist.find();


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





void TestRoom::Render()
{
	IMAGEMANAGER->ImageRander(testbg);
	Super::Render();
	static float a = 1.0f;
	const Location& playerLocation = player->GetLocation();
	const SIZE_F& playerSize = player->GetSize();
	D2D_POINT_2F playrLT = { (playerLocation.x - (playerSize.width / 2)) ,(playerLocation.y - (playerSize.height / 2)) };
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ playrLT.x,playrLT.y,playrLT.x + (playerSize.width ),playrLT.y + (playerSize.height) }, D2D::GetSingleton()->GetBrush());

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
