#pragma once
#include "Object.h"
struct TILE;

#define TILESIZE 32

class TileMap : public Object
{
public:
	struct TILE_F
	{
		D2D_RECT_F rc;
		int frameX;
		int frameY;
		float rotation;

		// 기하학 정보(충돌처리에 사용)
		GeometryInfo geometryinfo;

		bool GetisRender();

		TILE_F& operator = (TILE& tile);
	};
public:
	TileMap();
	~TileMap();
	HRESULT Init() override;
	void Release() override;
	void Render();

	void LoadTile(const char* fileName);
	void SetStartLocation(Location& location) { startLocation = location; }


private:
	ImageInfo TilesDrawinfo;
	TILE_F* tiles;
	UINT tile_X;
	UINT tile_Y;
	Location startLocation;
};

