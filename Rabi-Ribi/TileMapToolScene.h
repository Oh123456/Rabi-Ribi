#pragma once
#include "Object.h"

// 타일 하나의 사이즈
const SIZE tile_Size = { 32 , 32 };
// 샘플 타일의 x 갯수
const UINT sample_Tile_X = 30;//20;
// 샘플 타일의 y 갯수
const UINT sample_Tile_Y = 56;//9;


const UINT tile_Render_X = 25;
const UINT tile_Render_Y = 25;
const UINT tile_Render_Max = tile_Render_X * tile_Render_Y;

const UINT tileDrawX = 640;
const UINT tileDrawY = 480;

const LONG defaultFrame = 100;
const int maxAutoSave = 5;

#define OK_BUTTON_DEFAULT_COLOR  ColorF(0.0f, 0.2f, 0.9f)
#define OK_BUTTON_SELECT_COLOR  ColorF(1.0f, 0.2f, 0.9f)

enum class SizeKind
{
	None,
	X,
	Y,
};


enum class TERRAIN
{
	WALL,
	GRASS,
	EARTH,
	WATER,
	CEMENT,
	END
};

enum class GeometryKinds
{
	None,
	Triangle,
	Square,
	// 사다리꼴
	Trapezoid,

};

struct GeometryInfo
{
	GeometryKinds geometrykind;
	float width;
	float height;
	// 사다리꼴만 사용
	float _width;
	// 사다리꼴만 사용
	float _height;
	// 로테이션
	float rotation;
	
	void ReSet()
	{
		width = 0.0f;
		height = 0.0f;
		_width = 0.0f;
		_height = 0.0f;
		rotation = 0.0f;
		geometrykind = GeometryKinds::None;
	}
};


struct TILE
{
	RECT rc;
	int frameX;
	int frameY;
	TERRAIN  terrain;
	float rotation;

	// 기하학 정보(충돌처리에 사용)
	GeometryInfo geometryinfo;

};

struct SaveTILE
{
	int size[2];
	TILE tiles[100000];
};

struct LoadTILE
{
	int size[2];
	TILE* tiles;
};

struct SampleTile
{
	RECT rc;
	int frameX;
	int frameY;
};

struct SelectTile
{
	int frameX;
	int frameY;
	float rotation;
};


class TileMapToolScene : public Object
{


public:
	TileMapToolScene();
	~TileMapToolScene() override;

	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init() override;
	// 메모리 해제
	void Release() override;
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update() override;
	// 프레임 단위 출력 (이미지, 텍스트)
	void Render() override;

private:
	void Select(const RECT& samlpeRc);
	void RectSelectBegin();
	void RectSelectEnd(const RECT& samlpeRc);
	void Draw(const RECT& tileRc);
	// 사각형으로 그리기 시작 하는 시점
	void RectDrawBegin();
	// 사각형으로 그리기는중
	void RectDrawMove();
	// 사각형으로 그리기 끝나는 시점
	void RectDrawEnd(const RECT& tileRc);
	void SelectRectDrawShow(HDC hdc);
	void Erase(const RECT& tileRc);
	// 스포이드 영문단어
	void Dropper(const RECT& tileRc);
	void CleanAll();

	void SampleTileMoveSide(bool isLeft = true);
	void SampleTileMoveUp(bool isUp = true);

	void TileMoveSide(bool isLeft = true);
	void TileMoveUp(bool isUp = true);

	void SetGeometry(GeometryKinds kinds);
	void GetGeomrtyPoint(const GeometryInfo& geomrtyinfo);
	void GetGeomrtyPoint(ID2D1PathGeometry* const geometry,  const GeometryInfo& geomrtyinfo, RECT rect);

	void Save();
	void Save(const char* filename);
	void Load();
	void Resize(UINT width, UINT height);
	void NumberKeyInput(bool isSizex);
	void OnceNumberKey(int key, UINT& value);
	void QuickSave();
	void AutoSave();
	void ReDrawGeometry();
	void GeometryInfoKeyInput();
private:
	ID2D1Bitmap* sampleTile;
	ImageInfo sampleTileDraw;
	ImageInfo TilesDrawinfo;
	ImageInfo selectDrawinfo;
	ImageInfo saveButtoninfo;
	ImageInfo loadButtoninfo;
	ImageInfo exitButtoninfo;
	ImageInfo okButtoninfo;
	Color okButtonColor;


	// 메인 타일
	TILE* tiles;// [tile_X * tile_Y];
	// 샘플 타일
	SampleTile samlpeTile[sample_Tile_X * sample_Tile_Y];
	// 선택 타일
	SelectTile selectTile;
	vector<SelectTile> selectTiles;
	SIZE selectSize;

	bool isSelectTileRender;
	bool isRectDraw;
	// 그리는 타일이 타일 렌더갯수보다 많다면
	bool isTileOver;
	bool isCollisionLayer;
	SizeKind sizeKind;
	// 자리수
	int numCount;
	// 오토세이브 카운트
	int autoSaveCount;

	RECT rectDraw;
	RECT rectSelect;

	// 세이브 로드 버튼
	RECT rcSace;
	RECT rcLoad;
	RECT rcExit;

	RECT rcOkButton;
	RECT rcSizeX;
	RECT rcSizeY;

	// 타일 갯수
	UINT tile_X; 
	UINT tile_Y; 

	UINT temptile_X;
	UINT temptile_Y;

	bool isSpamlpeTileOver;
	RECT samlpeTileRect;
	SIZE samlpeTileRenderSize;
	// 샘플 타일이 이동했을시 타일 선택할때 보정값
	POINT samlpeTileMovepos;
	POINT moveFrame;
	POINT tileCamePos;

	ID2D1SolidColorBrush* brush;

	// 충돌박스
	ID2D1PathGeometry* geometry;
	GeometryInfo geometryinfo;
	ID2D1PathGeometry** tilesgeometry;
	//ID2D1PathGeometry* mp_path_geometry2;


	TimerHandle autoSaveTimerHandle;

};

