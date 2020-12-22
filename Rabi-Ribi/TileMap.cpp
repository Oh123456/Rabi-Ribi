#include "TileMap.h"
#include "TileMapToolScene.h"
#include"D2DGraphic.h"

bool TileMap::TILE_F::GetisRender()
{
	if ((frameX == defaultFrame) &
		(frameY == defaultFrame))
		return false;
	return true;
}

TileMap::TILE_F& TileMap::TILE_F::operator = (TILE& tile)
{
	this->rc.left = (float)tile.rc.left;
	this->rc.top = (float)tile.rc.top;
	this->rc.right = (float)tile.rc.right;
	this->rc.bottom = (float)tile.rc.bottom;
	this->geometryinfo = tile.geometryinfo;
	this->frameX = tile.frameX;
	this->frameY = tile.frameY;
	this->rotation = tile.rotation;
	return *this;
}


TileMap::TileMap()
{
}

TileMap::~TileMap()
{
	this->Release();
}

HRESULT TileMap::Init()
{
	TilesDrawinfo.imageName = L"샘플타일";
	TilesDrawinfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	TilesDrawinfo.atlasInfo.frameSize = { TILESIZE,TILESIZE };
	TilesDrawinfo.atlasInfo.frame = { 0,0 };
	TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(0, { 0.0f,0.0f });
	startLocation = { 0.0f,0.0f };
	return S_OK;
}

void TileMap::Release()
{
	SAFE_ARR_DELETE(tiles);
}

void TileMap::LoadTile(const char * fileName)
{
	DWORD readByte;
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	TILE* tempTile;

	int size[2];
	ReadFile(hFile, size, 2 * sizeof(int), &readByte, NULL);
	tile_X = size[0];
	tile_Y = size[1];
	tiles = new TILE_F[tile_X*tile_Y];
	tempTile = new TILE[tile_X*tile_Y];
	ReadFile(hFile, tempTile, size[0] * size[1] * sizeof(TILE), &readByte, NULL);
	for (int i = 0; (UINT)i < tile_Y; i++)
	{
		for (int j = 0; (UINT)j < tile_X; j++)
		{
			// 맵툴에서는 64 *64 사이즈엿으나  인겜에서는 32*32 사이즈로 변경
			SetRect(&tempTile[i * tile_X + j].rc,
				j * TILESIZE, i * TILESIZE,
				(j + 1) * TILESIZE, (i + 1) * TILESIZE);
			tempTile[i * tile_X + j].geometryinfo.width /= 2;
			tempTile[i * tile_X + j].geometryinfo._width /= 2;
			tempTile[i * tile_X + j].geometryinfo.height /= 2;
			tempTile[i * tile_X + j].geometryinfo._height /= 2;
			tiles[i * tile_X + j] = tempTile[i * tile_X + j];
		}
	}
	CloseHandle(hFile);
}


void TileMap::Render()
{
	D2D_RECT_F tilerc; 
	// 보정값 
	D2D_POINT_2F correctionValue = {startLocation.x + TILESIZE / 2 ,startLocation.y + TILESIZE / 2 };
	for (int i = 0; (UINT)i < tile_X* tile_Y; i++)
	{
		if (!tiles[i].GetisRender())
			continue;
		tilerc = tiles[i].rc;
		TilesDrawinfo.imageLocation = { (float)tilerc.left + correctionValue.x,(float)tilerc.top + correctionValue.y };
		TilesDrawinfo.atlasInfo.frame.x = tiles[i].frameX;
		TilesDrawinfo.atlasInfo.frame.y = tiles[i].frameY;
		TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(tiles[i].rotation, { TILESIZE / 2.0f,  TILESIZE / 2.0f })
												///약간의 틈세가 있어서 그걸 매워야하는 스케일 충돌처리할때도 해야한다 기억하자
											* Matrix3x2F::Scale({ 1.1f,1.1f }, { TILESIZE / 2.0f,  TILESIZE / 2.0f });
		IMAGEMANAGER->ImageRander(TilesDrawinfo);
	}

	//D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({4.0f,4.0f}));
}

