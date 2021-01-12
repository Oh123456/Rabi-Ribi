#include "TileMap.h"
#include "TileMapToolScene.h"
#include "GeometryCollision.h"
#include "D2DGraphic.h"

bool TILE_F::GetisRender()
{
	if ((frameX == defaultFrame) &
		(frameY == defaultFrame))
		return false;
	return true;
}

TILE_F& TILE_F::operator = (TILE& tile)
{
	this->rc.left = (float)tile.rc.left;
	this->rc.top = (float)tile.rc.top;
	this->rc.right = (float)tile.rc.right;
	this->rc.bottom = (float)tile.rc.bottom;
	this->geometryinfo = tile.geometryinfo;
	this->frameX = tile.frameX;
	this->frameY = tile.frameY;
	this->rotation = tile.rotation;
	this->isReverse = tile.isReverse;
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
//	TilesDrawinfo.atlasInfo.isCostumAtlas = true;
	TilesDrawinfo.atlasInfo.costumAtlasSize = { 0,0,0,0 };
	TilesDrawinfo.atlasInfo.frameSize = { 32.0f,32.0f };
	TilesDrawinfo.atlasInfo.frame = { 0,0 };
	TilesDrawinfo.scaleInfo.scaleSize = { 1.0625f,1.0625f };
	TilesDrawinfo.scaleInfo.scaleCenterPoint= { TILESIZE / 3.0f,  TILESIZE / 3.0f };
	TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(0, { 0.0f,0.0f });
	location = { 0.0f,0.0f };

	return S_OK;
}

void TileMap::Release()
{
	Super::Release();
	SAFE_ARR_DELETE(tiles);
	SafemapRelease(collisionList);
#ifdef _DEBUG
	for (int i = 0; (UINT)i < tile_X*tile_Y;i++)
		SAFE_RELEASE(debug_Tilesgeometry[i]);
#endif // _DEBUG

}

void TileMap::LoadTile(const char* fileName)
{
	string sfileName = fileName;
	wstring wfileName;
	wfileName.assign(sfileName.begin(), sfileName.end());
	wstring openFileName;
	openFileName = DefaultDirectory + DefaultStagePath + wfileName;

	DWORD readByte;
	HANDLE hFile = CreateFileW(openFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	TILE* tempTile;

	int size[2];
	ReadFile(hFile, size, 2 * sizeof(int), &readByte, NULL);
	tile_X = size[0];
	tile_Y = size[1];
	tiles = new TILE_F[tile_X*tile_Y];
	tempTile = new TILE[tile_X*tile_Y];
#ifdef _DEBUG
	debug_Tilesgeometry = new ID2D1PathGeometry*[tile_X*tile_Y];
	isDebug_Render = false;
#endif // _DEBUG
	ReadFile(hFile, tempTile, size[0] * size[1] * sizeof(TILE), &readByte, NULL);
	ID2D1PathGeometry* pathGeometry;
	ID2D1Factory* d2dFactory = D2D::GetSingleton()->GetD2DFactory();
	int index;
	for (int i = 0; (UINT)i < tile_Y; i++)
	{
		for (int j = 0; (UINT)j < tile_X; j++)
		{
			index = i * tile_X + j;
			if (index == 527)
				index = 527;
			// 맵툴에서는 64 *64 사이즈엿으나  인겜에서는 32*32 사이즈로 변경
			SetRect(&tempTile[index].rc,
				j * TILESIZE , i * TILESIZE,
				(j + 1) * TILESIZE, (i + 1) * TILESIZE);
			tempTile[index].geometryinfo.width /= 2;
			tempTile[index].geometryinfo._width /= 2;
			tempTile[index].geometryinfo.height /= 2;
			tempTile[index].geometryinfo._height /= 2;
			tiles[index] = tempTile[index];
			tiles[index].rc.left -= j *		0.8f;
			tiles[index].rc.top -= i *		0.8f;
			tiles[index].rc.right -= j *	0.8f;
			tiles[index].rc.bottom -= i *	0.8f;
			tiles[index].SetLocation({ tiles[index].rc.left + 16.0f, tiles[index].rc.top + 16.0f });
			tiles[index].SetSize({32.0f,32.0f});
			if (tempTile[index].GetisRender())
				renderList.push_back(&tiles[i * tile_X + j]);
			int geomttykind = Cast<int>(tempTile[index].geometryinfo.geometrykind);
			if ((tempTile[index].geometryinfo.geometrykind != GeometryKinds::None) & (geomttykind > 0))
			{
				pathGeometry = nullptr;
				d2dFactory->CreatePathGeometry(&pathGeometry);
				GetGeomrtyPoint(pathGeometry, tiles[index].geometryinfo, {0.0f,0.0f,32.0f,32.0f});
				GeometryCollision* geometryCollision = new GeometryCollision;
				geometryCollision->SetCollision(pathGeometry,&tiles[index]);
				geometryCollision->SetGeometryInfo(tiles[index].geometryinfo);
				CollisionIndex index;
				index.index = i * tile_X + j;
				index.x = j;
				index.y = i;
				index.tileX_Size = tile_X;
				collisionList.insert(make_pair(index, geometryCollision));
			}

#ifdef _DEBUG
			debug_Tilesgeometry[i * tile_X + j] = nullptr;
#endif // _DEBUG
		}
	}
	CloseHandle(hFile);

	CAMERA->SetMapMaxLocation({ (float)tile_X * 32.0f ,(float)tile_Y* 32.0f });
}

void TileMap::Update()
{
#ifdef _DEBUG
	if (KEYMANAGER->IsOnceKeyDown(VK_TAB))
		isDebug_Render = !isDebug_Render;
#endif

}

void TileMap::Render()
{
	ImageManager* imageManager = IMAGEMANAGER;      
	D2D_RECT_F tilerc; 
	// 보정값 
	location = CAMERA->GetLocation();
	D2D_POINT_2F correctionValue = {location.x -16.0f ,location.y -16.0f };
	list<TILE_F*>::const_iterator c_it;
	TILE_F* tile;
	for (c_it = renderList.begin();c_it != renderList.end(); c_it++)
	{
		tile = *c_it;
		tilerc = tile->rc;
		TilesDrawinfo.imageLocation = { tilerc.left  - correctionValue.x,  tilerc.top - correctionValue.y  };
		tile->SetLocation(TilesDrawinfo.imageLocation);
		TilesDrawinfo.atlasInfo.frame.x = tile->frameX;
		TilesDrawinfo.atlasInfo.frame.y = tile->frameY;
		TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(tile->rotation, { TILESIZE / 2.0f,  TILESIZE / 2.0f });
		if (tile->isReverse)
			TilesDrawinfo.affineMatrix = TilesDrawinfo.affineMatrix * Matrix3x2F::Scale({ -1.0f,1.0f }, { TILESIZE / 2.0f,  TILESIZE / 2.0f });
		imageManager->ImageRander(TilesDrawinfo);              

	}
#ifdef _DEBUG
	if (isDebug_Render)
	{
		for (c_it = renderList.begin();c_it != renderList.end(); c_it++)
		{
			tile = *c_it;
			for (int i = 0; (UINT)i < tile_X*tile_Y; i++)
			{
				if (debug_Tilesgeometry[i] == nullptr)
				{
					D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&debug_Tilesgeometry[i]);
					GetGeomrtyPoint(debug_Tilesgeometry[i], tile->geometryinfo, tile->rc);
					D2D::GetSingleton()->GetBrush()->SetColor(D2D1::ColorF(0xffffff));
					D2D::GetSingleton()->GetD2DRenderTarget()->FillGeometry(debug_Tilesgeometry[i], D2D::GetSingleton()->GetBrush());
					SAFE_RELEASE(debug_Tilesgeometry[i]);
				}
			}
		}
	}
#endif

	
}

void TileMap::GetGeomrtyPoint(ID2D1PathGeometry* const geometry, const GeometryInfo & geomrtyinfo, D2D_RECT_F rect)
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
		D2D1_POINT_2F point[2] = { rect.left +geomrtyinfo.width ,rect.bottom ,
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
		D2D1_POINT_2F point[3] = {	{rect.left + geomrtyinfo.width,rect.bottom},
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


