#include "CollisionManager.h"
#include "Character.h"
#include "Actor.h"
#include "Erina.h"
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
}

void CollisionManager::Render()
{
	Super::Render();
	SideCollosion[2];
	for (int i = 0; i < 2; i++)
	{
		if (SideCollosion[i])
			D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(SideCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());
	}
	D2D::GetSingleton()->GetBrush()->SetColor({ 1.0f,0,0.0f ,1.0f});
	for (int i = 0; i < 4; i++)
	{
		if (battomCollosion[i])
			D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(battomCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());
	}

	D2D::GetSingleton()->GetBrush()->SetColor({ 1.0f,0.0f,1.0f,1.0f });
	for (int i = 0; i < 3; i++)
	{
		if (topCollosion[i])
			D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(topCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());
	}

	D2D::GetSingleton()->GetBrush()->SetColor({ 0,0,1.0f,1.0f });
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
		}
	}
}

void CollisionManager::TerrainCollisionCheck()
{
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
			actor = (*c_setier).actor;
			actorCollision = const_cast<ID2D1PathGeometry*>(actor->GetCollisionGeomtry());
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
				cplayer->MoveCancel(side, up);
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
	int LT_x = (int)(actor->GetLocation().x / (32.0f - 0.8f));
	int LT_y = (int)(actor->GetLocation().y / (32.0f - 0.8f));
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
	// 벽아래는 갈수없기에 충돌 영역제거
	for (int i = 0; i < 2; i++)
	{
		if ((SideCollosion[i] != nullptr) & (battomCollosion[i * 2] != nullptr))
			battomCollosion[i * 2] = nullptr;
	}
	Character* character = Cast<Character>(actor);
	bool isFalling = true;
	for (int i = 0; i < 4; i++)
	{
		if (battomCollosion[i])
		{
			//D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(battomCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());
			if (battomCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionGeomtry()), player_LTLocation))
			{
			
				if (character)
				{
					if ((character->GetFalling()))
					{
						isFalling = false;
						
						
						while (battomCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionGeomtry()), player_LTLocation))
							player_LTLocation.y -= 0.1f;
						
						
					}
				}
				Object* onwer = Cast<Object>(battomCollosion[i]->GetOwner());
				//actor->onHit.Execute(onwer);
			}
		}
	}
	if (character)
		character->SetFalling(isFalling);
	
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
	int LT_x = (int)(actor->GetLocation().x / (32.0f - 0.8f));
	int LT_y = (int)(actor->GetLocation().y / (32.0f - 0.8f));
	for (int i = 0; i < 2; i++)
	{

		find.index = (LT_x + (i % 2) * 2  -1) + (LT_y) * tileX_Size;
		c_it = collisionlist.find(find);
		SideCollosion[i] = nullptr;
		if (c_it != collisionlist.end())
			SideCollosion[i] = c_it->second;
	}

	Character* character = Cast<Character>(actor);
	for (int i = 0; i < 2; i++)
	{
		
		if (SideCollosion[i])
		{
			TILE_F* tile = Cast<TILE_F>(SideCollosion[i]->GetOwner());
			//D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(SideCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());
			if (SideCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionGeomtry()), player_LTLocation))
			{

				if (((tile->isReverse) & (i == 0)) | ((tile->geometryinfo.geometrykind == GeometryKinds::Square)))
				{
					if (character)
						return true;
				}
				else if (i == 0)
				{
					while (SideCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionGeomtry()), player_LTLocation))
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
						while (SideCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionGeomtry()), player_LTLocation))
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
	int LT_x = (int)(actor->GetLocation().x / (32.0f - 0.8f));
	int LT_y = (int)(actor->GetLocation().y / (32.0f - 0.8f));
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

	Character* character = Cast<Character>(actor);
	bool isFalling = true;
	for (int i = 0; i < 3; i++)
	{
		if (topCollosion[i])
		{
	
			//D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle(Cast<TILE_F>(topCollosion[i]->GetOwner())->rc, D2D::GetSingleton()->GetBrush());

			if (topCollosion[i]->CollisionHitCheck(Cast<ID2D1PathGeometry>(actor->GetCollisionGeomtry()), player_LTLocation))
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