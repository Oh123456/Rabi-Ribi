#pragma once
#include "Object.h"

const SIZE SelectTile_Size = { 32 , 32 };
// Ÿ�� �ϳ��� ������
const SIZE tile_Size = { 64 , 64 };
// ���� Ÿ���� x ����
const UINT sample_Tile_X = 30;//20;
// ���� Ÿ���� y ����
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

	// ������ ����(�浹ó���� ���)
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

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

private:
	// ���̾� ���� ���̾�� 1���̰� ������ ���߿� �׷�����.
	void LayerTileRender();
	void Select(const RECT& samlpeRc);
	void RectSelectBegin();
	void RectSelectEnd(const RECT& samlpeRc);
	void Draw(const RECT& tileRc);
	// �簢������ �׸��� ���� �ϴ� ����
	void RectDrawBegin();
	// �簢������ �׸������
	void RectDrawMove();
	// �簢������ �׸��� ������ ����
	void RectDrawEnd(const RECT& tileRc);
	void SelectRectDrawShow(HDC hdc);
	void Erase(const RECT& tileRc);
	// �����̵� �����ܾ�
	void Dropper(const RECT& tileRc);
	void CleanAll();
	// �����Ⱚ û��
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


	// ���� Ÿ��
	TILE* tiles;// [tile_X * tile_Y];
	// ���� Ÿ��
	SampleTile samlpeTile[sample_Tile_X * sample_Tile_Y];
	// ���� Ÿ��
	SelectTile selectTile;
	vector<SelectTile> selectTiles;
	SIZE selectSize;

	bool isSelectTileRender;
	bool isRectDraw;
	// �׸��� Ÿ���� Ÿ�� ������������ ���ٸ�
	bool isTileOver;
	// �浹ó�� ���� ǥ��
	bool isCollisionLayer;
	bool isTerraimLayer; 
	// ������ �ѹ��������� ������ ���� �⺻  ��ΰ� �ٲ�� �־���
	bool isOpen;
	// ���ڴ� ǥ�� 
	bool IsGridline;
	// ���̾� ǥ��
	bool isLayerTileRender;
	SizeKind sizeKind;
	// �ڸ���
	int numCount;
	// ���似�̺� ī��Ʈ
	int autoSaveCount;

	RECT rectDraw;
	RECT rectSelect;

	// ���̺� �ε� ��ư
	RECT rcSave;
	RECT rcLoad;
	RECT rcLayerLoad;
	RECT rcExit;

	RECT rcOkButton;
	RECT rcSizeX;
	RECT rcSizeY;

	// Ÿ�� ����
	UINT tile_X; 
	UINT tile_Y; 

	// ���� ���̾�
	LayerTile* layerTile;

	UINT temptile_X;
	UINT temptile_Y;

	bool isSpamlpeTileOver;
	RECT samlpeTileRect;
	SIZE samlpeTileRenderSize;
	// ���� Ÿ���� �̵������� Ÿ�� �����Ҷ� ������
	POINT samlpeTileMovepos;
	POINT moveFrame;
	POINT tileCamePos;

	ID2D1SolidColorBrush* brush;

	// �浹�ڽ�
	ID2D1PathGeometry* geometry;
	GeometryInfo geometryinfo;
	ID2D1PathGeometry** tilesgeometry;
	//ID2D1PathGeometry* mp_path_geometry2;
	deque<Worklist*> worklist;

	TimerHandle autoSaveTimerHandle;
	

};

