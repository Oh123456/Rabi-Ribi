#pragma once
#include "Object.h"

// Ÿ�� �ϳ��� ������
const SIZE tile_Size = { 32 , 32 };
// ���� Ÿ���� x ����
const UINT sample_Tile_X = 30;//20;
// ���� Ÿ���� y ����
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
	// ��ٸ���
	Trapezoid,

};

struct GeometryInfo
{
	GeometryKinds geometrykind;
	float width;
	float height;
	// ��ٸ��ø� ���
	float _width;
	// ��ٸ��ø� ���
	float _height;
	// �����̼�
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

	// ������ ����(�浹ó���� ���)
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

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

private:
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
	bool isCollisionLayer;
	SizeKind sizeKind;
	// �ڸ���
	int numCount;
	// ���似�̺� ī��Ʈ
	int autoSaveCount;

	RECT rectDraw;
	RECT rectSelect;

	// ���̺� �ε� ��ư
	RECT rcSace;
	RECT rcLoad;
	RECT rcExit;

	RECT rcOkButton;
	RECT rcSizeX;
	RECT rcSizeY;

	// Ÿ�� ����
	UINT tile_X; 
	UINT tile_Y; 

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


	TimerHandle autoSaveTimerHandle;

};

