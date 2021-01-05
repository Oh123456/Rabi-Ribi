#include "CollisionManager.h"
#include "Character.h"
#include "Actor.h"
#include "Erina.h"
#include "Enemy.h"
#include "TileMap.h"
#include "GeometryCollision.h"
#include "D2DGraphic.h"


CollisionManager::CollisionManager() : 
	tileMap(nullptr) 
{
	actors.clear();
}

CollisionManager::~CollisionManager()
{
}

HRESULT CollisionManager::Init()
{

	return S_OK;
}

void CollisionManager::Release()
{
	Super::Release();
	tileMap = nullptr;
	actors.clear();
}

void CollisionManager::Update()
{
	Super::Update();
	TerrainCollisionCheck();
	SplitScreen();
	for (int i = 0; i < 4; i++)
		ActorCollision(collision[i]);
}

void CollisionManager::Render()
{
	Super::Render();
#ifdef _DEBUG

	list<GeometryCollision*>::const_iterator c_it;
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	int count = 0;
	GeometryCollision* collision = nullptr;
	for (c_it = debug_collisionBoxlist.begin(); c_it != debug_collisionBoxlist.end(); c_it++)
	{
		count++;
		if (count <= 2)
			brush->SetColor({ 0,0,1.0f,1.0f });
		else if (count <= 6)
			brush->SetColor({ 1.0f,0.0f,1.0f,1.0f });
		else
			brush->SetColor({ 1.0f,0,0.0f ,1.0f });

		collision = *c_it;
		if (collision)
		{
			TILE_F* tilef = Cast<TILE_F>(collision->GetOwner());
			D2D1_RECT_F debug_rc = { tilef->GetLocation().x - 16.0f,tilef->GetLocation().y - 16.0f,
												tilef->GetLocation().x + 16.0f ,tilef->GetLocation().y + 16.0f };
			D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(debug_rc, brush);
		}
		if (count == 9)
			count = 0;
	}
	brush->SetColor({ 0,0,1.0f,1.0f });
#endif // _DEBUG

	
}

void CollisionManager::SettingActor(Object * secen)
{
	list<Object*>* allCalss =  secen->GetChilds();
	list<Object*>::const_iterator c_it;

	Object* object = nullptr;
	Erina* player = nullptr;
	Actor* actor = nullptr;
	TileMap* tileMap = nullptr;
	ActorKey_Value actor_Value;
	actor_Value.actor = nullptr;
	for (c_it = allCalss->begin(); c_it != allCalss->end(); c_it++)
	{

		object = *c_it;
		actor_Value.actor = nullptr;
		player = Cast<Erina>(object);
		if (player)
		{
			actor_Value.actor = player;
			actors.insert(actor_Value);
			SettingActor(player);
			continue;
		}
		tileMap = Cast<TileMap>(object);
		if (tileMap)
		{
			this->tileMap = tileMap;
			continue;
		}
		actor = Cast<Actor>(object);
		if (actor)
		{
			actor_Value.actor = actor;
			actors.insert(actor_Value);
			SettingActor(actor);
		}
	}
}

void CollisionManager::TerrainCollisionCheck()
{
#ifdef _DEBUG
	debug_collisionBoxlist.clear();
#endif // _DEBUG

	if (tileMap)
	{
		map<CollisionIndexInfo, GeometryCollision*> collisionlist = tileMap->GetcollisionList();
		map<CollisionIndexInfo, GeometryCollision*>::const_iterator c_it;
		if (collisionlist.empty())
			return;
		Actor* actor = nullptr;

		set<ActorKey_Value>::const_iterator c_setier;
		ID2D1PathGeometry* actorCollision = nullptr;
		Location actorLocation;
		SIZE_F actorSize;
		Object* object = nullptr;
		D2D_POINT_2F actorLT;// = { (playerLocation.x - (playerSize.width / 2)) ,(playerLocation.y - (playerSize.height / 2)) };
		GeometryCollision* tileCollision = nullptr;
		Character* cplayer = Cast<Character>(actor);


		for (c_setier = actors.begin(); c_setier != actors.end(); c_setier++)
		{
			ZeroMemory(SideCollosion, sizeof(GeometryCollision*) * 2);
			ZeroMemory(battomCollosion, sizeof(GeometryCollision*) * 4);
			ZeroMemory(topCollosion, sizeof(GeometryCollision*) * 3);
			actor = (*c_setier).actor;
			if (actor->GetIgnoreTerrain())
				continue;
			actorCollision = const_cast<ID2D1PathGeometry*>(actor->GetCollisionPathGeomtry());
			actorLocation = actor->GetGeomtryLocation();
			actorSize = actor->GetSize();

			actorLT = { (actorLocation.x - (actorSize.width / 2)) ,(actorLocation.y - (actorSize.height / 2)) };

			c_it = collisionlist.begin();
			if (c_it == collisionlist.end())
				return;
			CollisionIndexInfo begin = c_it->first;
			UINT tileX_Size = begin.tileX_Size;
			cplayer = Cast<Character>(actor);
			//D2D::GetSingleton()->BeginDraw();
			TerrainBottomCollision(actor, tileX_Size, actorLT);
			bool side = TerrainSideCollision(actor, tileX_Size, actorLT);
			bool up = TerrainTopCollision(actor, tileX_Size, actorLT);
			//D2D::GetSingleton()->EndDraw();
			if (cplayer)
			{
				cplayer->MoveToNewGeomtryLocation(actorLT);
				cplayer->MoveCancel(side,false);
				cplayer->MoveCancel(up, up);
				//cplayer->MoveCharacter();
			}
		}

		// 플레이어의 LT;
		
		//cplayer->SetFalling(true);
		bool ishit = false;
		// playerLocation.x;

		//playerindex[0] = { LT_x , LT_y };
		//playerindex[1] = { LT_x + 1 , LT_y };
		//playerindex[2] = { LT_x , LT_y + 1 };
		//playerindex[3] = { LT_x + 1, LT_y + 1 };


	}
}

void CollisionManager::TerrainBottomCollision(Actor* actor, UINT tileX_Size, Location & player_LTLocation)
{
	map<CollisionIndexInfo, GeometryCollision*> collisionlist = tileMap->GetcollisionList();
	map<CollisionIndexInfo, GeometryCollision*>::const_iterator c_it;
	if (collisionlist.empty())
		return;

	c_it = collisionlist.begin();
	if (c_it == collisionlist.end())
		return;
	CollisionIndexInfo begin = c_it->first;
	CollisionIndexInfo find;
	int LT_x = (int)((actor->GetLocation().x + CAMERA->GetLocation().x)/ (32.0f - 0.8f));
	int LT_y = (int)((actor->GetLocation().y + CAMERA->GetLocation().y)/ (32.0f - 0.8f));
	for (int i = 0; i < 4; i++)
	{
		if (i == 3)
			find.index = (LT_x) + (LT_y) * tileX_Size;
		else
			find.index = (LT_x - 1 + i) + (LT_y + 1 ) * tileX_Size;
		c_it = collisionlist.find(find);
		battomCollosion[i] = nullptr;
		if (c_it != collisionlist.end())
			battomCollosion[i] = c_it->second;
	}
	// 처리부는 TerrainSideCollision으로 이동


}

bool CollisionManager::TerrainSideCollision(Actor * actor, UINT tileX_Size, Location & player_LTLocation)
{
	map<CollisionIndexInfo, GeometryCollision*> collisionlist = tileMap->GetcollisionList();
	map<CollisionIndexInfo, GeometryCollision*>::const_iterator c_it;
	if (collisionlist.empty())
		return false;

	c_it = collisionlist.begin();
	if (c_it == collisionlist.end())
		return false;
	CollisionIndexInfo begin = c_it->first;
	CollisionIndexInfo find;
	int LT_x = (int)((actor->GetLocation().x + CAMERA->GetLocation().x) / (32.0f - 0.8f));
	int LT_y = (int)((actor->GetLocation().y + CAMERA->GetLocation().y) / (32.0f - 0.8f));
	for (int i = 0; i < 2; i++)
	{

		find.index = (LT_x + (i % 2) * 2  -1) + (LT_y) * tileX_Size;
		c_it = collisionlist.find(find);
		SideCollosion[i] = nullptr;
		if (c_it != collisionlist.end())
			SideCollosion[i] = c_it->second;
	}
	// 벽아래는 갈수없기에 충돌 영역제거
	for (int i = 0; i < 2; i++)
	{
		if ((SideCollosion[i] != nullptr) & (battomCollosion[i * 2] != nullptr))
			battomCollosion[i * 2] = nullptr;
		if ((SideCollosion[i] == battomCollosion[3]))
			battomCollosion[3] = nullptr;
	}
#ifdef _DEBUG
	for (int i = 0; i < 2; i++)
		debug_collisionBoxlist.push_back(SideCollosion[i]);
	for (int i = 0; i < 4; i++)
		debug_collisionBoxlist.push_back(battomCollosion[i]);

#endif // _DEBUG

	// 바닥부 충돌처리 
// 순서를 바꾸면 공중에떠있는 버그가 있어
// 충돌 타일은 먼저 검사후 여기서 충동처리를 해준다
	Character* character = Cast<Character>(actor);
	bool isFalling = true;
	for (int i = 0; i < 4; i++)
	{
		if (battomCollosion[i])
		{
			if (battomCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionPathGeomtry()), player_LTLocation))
			{

				if (character)
				{
					//if ((character->GetFalling()))
					{
						isFalling = false;
						while (battomCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionPathGeomtry()), player_LTLocation))
							player_LTLocation.y -= 0.1f;
					}
				}
			}
		}
	}
	if (character)
		character->SetFalling(isFalling);

	//Character* character = Cast<Character>(actor);
	for (int i = 0; i < 2; i++)
	{
		
		if (SideCollosion[i])
		{
			TILE_F* tile = Cast<TILE_F>(SideCollosion[i]->GetOwner());
			//D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(SideCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());
			if (SideCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionPathGeomtry()), player_LTLocation))
			{

				if (((tile->isReverse) & (i == 0)) | ((tile->geometryinfo.geometrykind == GeometryKinds::Square)))
				{
					if (character)
						return true;
				}
				else if (i == 0)
				{
					while (SideCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionPathGeomtry()), player_LTLocation))
						player_LTLocation.y -= 0.1f;
					Cast<Character>(actor)->SetFalling(false);
				}
				else
				{
					if (((!tile->isReverse) & (i == 1)) | ((tile->geometryinfo.geometrykind == GeometryKinds::Square)))
					{
						if (character)
							return true;
					}
					else
					{
						while (SideCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionPathGeomtry()), player_LTLocation))
							player_LTLocation.y -= 0.1f;
						Cast<Character>(actor)->SetFalling(false);
					}
				}
			}
		}
	}

	return false;
}

bool CollisionManager::TerrainTopCollision(class Actor* actor, UINT tileX_Size, const Location& player_LTLocation)
{
	map<CollisionIndexInfo, GeometryCollision*> collisionlist = tileMap->GetcollisionList();
	map<CollisionIndexInfo, GeometryCollision*>::const_iterator c_it;
	if (collisionlist.empty())
		return false;

	c_it = collisionlist.begin();
	if (c_it == collisionlist.end())
		return false;
	CollisionIndexInfo begin = c_it->first;
	CollisionIndexInfo find;
	int LT_x = (int)((actor->GetLocation().x + CAMERA->GetLocation().x) / (32.0f - 0.8f));
	int LT_y = (int)((actor->GetLocation().y + CAMERA->GetLocation().y) / (32.0f - 0.8f));
	for (int i = 0; i < 3; i++)
	{
		find.index = (LT_x + i - 1) + (LT_y - 1) * tileX_Size;
		
		c_it = collisionlist.find(find);
		topCollosion[i] = nullptr;
		if (c_it != collisionlist.end())
			topCollosion[i] = c_it->second;
	}

	// 벽위는 갈수없기에 충돌 영역제거
	for (int i = 0; i < 2; i++)
	{
		if ((SideCollosion[i] != nullptr) & (topCollosion[i * 2] != nullptr))
			topCollosion[i * 2] = nullptr;
	}

#ifdef _DEBUG
	for (int i = 0; i < 3; i++)
		debug_collisionBoxlist.push_back(topCollosion[i]);
#endif // _DEBUG

	Character* character = Cast<Character>(actor);
	bool isFalling = true;
	for (int i = 0; i < 3; i++)
	{
		if (topCollosion[i])
		{
	
			//D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(topCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());

			if (topCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionPathGeomtry()), player_LTLocation))
			{
				isFalling = false;
				if (character)
				{
					
					{
						float a = topCollosion[i]->GetGeometryInfo().height;
						Location actorLocation = actor->GetLocation();
						return true;
					}
				}
			}
		}
	}
	return false;
}

void CollisionManager::ActorCollision()
{
	if ((!actors.empty()) | (actors.size() > (size_t)(1)))
	{
		set<ActorKey_Value>::const_iterator c_it;
		set<ActorKey_Value>::const_iterator c_nowit;
		Actor* nowActor = nullptr;
		Actor* nextActor = nullptr;

		GeometryCollision* nowGeimetryCollision = nullptr;
		GeometryCollision* nextGeimetryCollision = nullptr;


		c_it = actors.begin();
		while (true)
		{
			nowActor = c_it->actor;
			if (nowActor == nullptr)
			{
				c_it++;
				if (c_it == actors.end())
					return;
			}
			else
			{
				c_nowit = c_it;
				break;
			}
		}

		nowGeimetryCollision = nowActor->GetCollisionGeomtry();
		while (true)
		{
			c_it++;
			if (c_it == actors.end())
			{
				c_nowit++;
				if (c_nowit == actors.end())
					return;
				nowActor = c_nowit->actor;
				c_it = c_nowit;
			}
			nextActor = c_it->actor;
			if (nextActor == nullptr)
				continue;
			nextGeimetryCollision = nextActor->GetCollisionGeomtry();
			bool isHit = nowGeimetryCollision->CollisionHitCheck(nextGeimetryCollision->GetGeometry(), nextActor->GetLocation());
			if (isHit)
			{
				nowActor->onHit.Execute(nextActor);
				nextActor->onHit.Execute(nowActor);
			}
		}
	}
}

void CollisionManager::ActorCollision(list<Actor*>& splitCollision)
{
	if ((!splitCollision.empty()) | (splitCollision.size() > (size_t)(1)))
	{
		list<Actor*>::const_iterator c_it;
		list<Actor*>::const_iterator c_nowit;
		Actor* nowActor = nullptr;
		Actor* nextActor = nullptr;
		Enemy* enemy = nullptr;

		GeometryCollision* nowGeimetryCollision = nullptr;
		GeometryCollision* nextGeimetryCollision = nullptr;
		GeometryCollision* seeAreaGeimetryCollision = nullptr;


		c_it = splitCollision.begin();


		for (c_nowit = splitCollision.begin(); c_nowit != splitCollision.end();)
		{
			nowActor = *c_nowit;
			nowGeimetryCollision = nowActor->GetCollisionGeomtry();
			c_nowit++;
			if (nowActor == nullptr)
				continue;
			for (c_it = c_nowit; c_it != splitCollision.end(); c_it++)
			{
				nextActor = *c_it;
				if (nextActor == nullptr)
					continue;

				nextGeimetryCollision = nextActor->GetCollisionGeomtry();
				bool isHit = nowGeimetryCollision->CollisionHitCheck(nextGeimetryCollision->GetGeometry(), nextActor->GetLTLocation());
				if (isHit)
				{
					nowActor->onHit.Execute(nextActor);
					nextActor->onHit.Execute(nowActor);
				}

				enemy = Cast<Enemy>(nowActor);
				if (enemy)
				{
					seeAreaGeimetryCollision = enemy->GetSeeArea();
					if (seeAreaGeimetryCollision)
					{
						bool isSee = seeAreaGeimetryCollision->CollisionHitCheck(nextGeimetryCollision->GetGeometry(), nextActor->GetLTLocation());
						if (isSee)
							enemy->onSee.Execute(nowActor);
					}
				}

				enemy = Cast<Enemy>(nextActor);
				if (enemy)
				{
					seeAreaGeimetryCollision = enemy->GetSeeArea();
					if (seeAreaGeimetryCollision)
					{
						bool isSee = seeAreaGeimetryCollision->CollisionHitCheck(nowGeimetryCollision->GetGeometry(), nowActor->GetLTLocation());
						if (isSee)
							enemy->onSee.Execute(nowActor);
					}
				}
			}
		}
	}
}

void CollisionManager::SplitScreen()
{
	Location centerPoint = { WINSIZE_X / (2.0f * CAMERA->GetZoom().x) , WINSIZE_Y / (2.0f * CAMERA->GetZoom().y) };
	bool quadrant[4];
	Location actorlocation;
	D2D1_RECT_F actorRc;
	SIZE_F actorCollisionSize;
	Actor* actor = nullptr;
	set<ActorKey_Value>::const_iterator c_it;
	for (int i = 0; i < 4; i++)
		collision[i].clear();
	
	for (c_it = actors.begin(); c_it != actors.end(); c_it++)
	{
		ZeroMemory(&actorlocation,sizeof(Location));
		ZeroMemory(&actorCollisionSize, sizeof(SIZE_F));
		ZeroMemory(&actorRc, sizeof(D2D1_RECT_F));
		ZeroMemory(&quadrant, sizeof(bool) * 4);
		actor = nullptr;
		actor = c_it->actor;
		if ((actor == nullptr) | (!actor->GetIsValid()) | (actor->GetCollisionGeomtry() == nullptr))
			continue;
		actorlocation = actor->GetLocation();
		actorCollisionSize = actor->GetSize();

		actorRc = { actorlocation.x - (actorCollisionSize.width / 2) , actorlocation.y - (actorCollisionSize.height / 2) ,
						actorlocation.x + (actorCollisionSize.width / 2) ,actorlocation.y + (actorCollisionSize.height / 2) };
		
		// 화면 밖에 있을경우 충돌 처리에서 제외한다
		if (	(actorRc.left > (float)WINSIZE_X) |
			(actorRc.right < 0.0f) |
			(actorRc.top > (float)WINSIZE_Y) |
			(actorRc.bottom < 0.0f))
			continue;


		if (actorRc.left < centerPoint.x)
		{
			if (actorRc.top < centerPoint.y)
			{
				quadrant[0] = true;
				if (actorRc.bottom > centerPoint.y)
					quadrant[2] = true;
			}
			else
				quadrant[2] = true;

			if (actorRc.right > centerPoint.x)
			{
				if (quadrant[0])
					quadrant[1] = true;
				if (quadrant[2])
					quadrant[3] = true;
			}
		}
		else
		{
			if (actorRc.top < centerPoint.y)
			{
				quadrant[1] = true;
				if (actorRc.bottom > centerPoint.y)
					quadrant[3] = true;
			}
			else
				quadrant[3] = true;
		}

		for (int i = 0; i < 4 ; i++)
		{
			if (quadrant[i])
				collision[i].push_back(actor);
		}

	}



}							
