#pragma once
#include "Object.h"

const SIZE SelectTile_Size = { 32 , 32 };
// 타일 하나의 사이즈
const SIZE tile_Size = { 64 , 64 };
// 샘플 타일의 x 갯수
const UINT sample_Tile_X = 30;//20;
// 샘플 타일의 y 갯수
const UINT sample_Tile_Y = 56;//9;

const UINT renderOffset = 64;
const UINT tile_Render_X = 12;
const UINT tile_Render_Y = 11;
const UINT tile_Render_Max = tile_Render_X * tile_Render_Y;

const UINT tileDrawX = 640;
const UINT tileDrawY = 480;

const LONG defaultFrame = 100;
const int maxAutoSave = 5;
const UINT maxWorklist = 200;

#define OK_BUTTON_DEFAULT_COLOR  ColorF(0.0f, 0.2f, 0.9f)
#define OK_BUTTON_SELECT_COLOR  ColorF(1.0f, 0.2f, 0.9f)

enum class SizeKind
{
	None,
	X,
	Y,
};




struct TILE
{
	RECT rc;
	int frameX;
	int frameY;
	TERRAIN  terrain;
	float rotation;
	bool isReverse = false;

	// 기하학 정보(충돌처리에 사용)
	GeometryInfo geometryinfo;

	bool GetisRender()
	{
		if ((frameX == defaultFrame) &
			(frameY == defaultFrame))
			return false;
		return true;
	}
};


struct Worklist
{
	UINT tile_X;
	UINT tile_Y;
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
	TERRAIN  terrain = TERRAIN::NOAML;
	bool isReverse = false;
};

struct LayerTile
{
	TILE* tiles;
	UINT tile_X;
	UINT tile_Y;
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
	// 레이어 렌더 레이어는 1개이고 무조건 난중에 그려진다.
	void LayerTileRender();
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
	// 쓰레기값 청소
	void CleanUP();

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
	void LayerLoad();
	void Resize(UINT width, UINT height);
	void NumberKeyInput(bool isSizex);
	void OnceNumberKey(int key, UINT& value);
	void QuickSave();
	void AutoSave();
	void ReDrawGeometry();
	void GeometryInfoKeyInput();
	void TileIndexMoveUP(bool isUP);
	void TileIndexMoveSide(bool isleft);

	void Undo();
	void WorklistAdd();
	void DeleteLayer();
private:
	ID2D1Bitmap* sampleTile;
	ImageInfo sampleTileDraw;
	ImageInfo TilesDrawinfo;
	ImageInfo selectDrawinfo;
	ImageInfo saveButtoninfo;
	ImageInfo loadButtoninfo;
	ImageInfo layerLoadButtoninfo;
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
	// 충돌처리 영역 표시
	bool isCollisionLayer;
	bool isTerraimLayer; 
	// 파일을 한번열었는지 파일을 열면 기본  경로가 바뀌여서 넣엇다
	bool isOpen;
	// 격자눈 표시 
	bool IsGridline;
	// 레이어 표시
	bool isLayerTileRender;
	SizeKind sizeKind;
	// 자리수
	int numCount;
	// 오토세이브 카운트
	int autoSaveCount;

	RECT rectDraw;
	RECT rectSelect;

	// 세이브 로드 버튼
	RECT rcSave;
	RECT rcLoad;
	RECT rcLayerLoad;
	RECT rcExit;

	RECT rcOkButton;
	RECT rcSizeX;
	RECT rcSizeY;

	// 타일 갯수
	UINT tile_X; 
	UINT tile_Y; 

	// 전방 레이어
	LayerTile* layerTile;

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
	deque<Worklist*> worklist;

	TimerHandle autoSaveTimerHandle;
	

};

