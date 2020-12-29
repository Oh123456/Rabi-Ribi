#pragma once
#include "Actor.h"
struct TILE;

#define TILESIZE 32


class TILE_F : public Actor
{
public:
	TILE_F() {};
	~TILE_F() override  {} ;
	D2D_RECT_F rc;
	int frameX;
	int frameY;
	float rotation;
	bool isReverse;
	// 기하학 정보(충돌처리에 사용)
	GeometryInfo geometryinfo;

	bool GetisRender();

	TILE_F& operator = (TILE& tile);
};

typedef struct CollisionIndexInfo
{
	bool operator<(const CollisionIndexInfo& src) const
	{
		if (this->index < src.index)
			return true;
		return false;
	}

	int index;
	UINT tileX_Size;
	int x;
	int y;
}CollisionIndex;

class TileMap : public Actor
{
	SUPER(Actor);
public:
	TileMap();
	~TileMap();
	HRESULT Init() override;
	void Release() override;
	void Render() override;
	void Update() override;

	void LoadTile(const char* fileName);
	void SetStartLocation(const Location& location) { this->location = location; }

	const list<TILE_F*>& GetRenderList() const { return renderList; }
	const map<CollisionIndexInfo, class GeometryCollision*>& GetcollisionList() const { return collisionList; }
private:
	void GetGeomrtyPoint(ID2D1PathGeometry* const geometry, const GeometryInfo& geomrtyinfo, D2D_RECT_F rect);
private:
	ImageInfo TilesDrawinfo;
	TILE_F* tiles;
	UINT tile_X;
	UINT tile_Y;
	//Location startLocation;
	list<TILE_F*> renderList;
	//list<class GeometryCollision*> collisionList;
	map<CollisionIndexInfo, class GeometryCollision*> collisionList;

#ifdef _DEBUG
	ID2D1PathGeometry** debug_Tilesgeometry;
	
	bool isDebug_Render;
#endif // _DEBUG

};

