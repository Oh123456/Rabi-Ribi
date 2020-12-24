#include "TileMapToolScene.h"
#include "D2DGraphic.h"


TileMapToolScene::TileMapToolScene()
{
	
}

TileMapToolScene::~TileMapToolScene()
{
}

HRESULT TileMapToolScene::Init()
{
	// 랜더 타겟 리사이즈
	SetWindowSize(0, 0, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	D2D::GetSingleton()->GetD2DRenderTarget()->Resize({ (UINT32)rect.right, (UINT32)rect.bottom });
	D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({ 1.0f,1.0f }));

	Resize((UINT)30, (UINT)11);


	if (tile_X * tile_Y <= tile_Render_Max)
		isTileOver = false;
	else
		isTileOver = true;
	tileCamePos = { 0,0 };
	samlpeTileRect = { WINSIZE_TILE_MAP_X - tileDrawX ,0, WINSIZE_TILE_MAP_X  , tileDrawY };
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->LoadPng(L"버튼", L"Button/Button");
	imageManager->LoadPng(L"탈출", L"Button/ExitButton");
	sampleTile = ImageManager::GetSingleton()->FindImage(L"샘플타일");
	moveFrame = { 0,0 };
	D2D1_SIZE_F sampleTileSize = sampleTile->GetSize();
	if ((int)sampleTileSize.width > tileDrawX || (int)sampleTileSize.height > tileDrawY)
	{
		isSpamlpeTileOver = true;
		samlpeTileRenderSize = { tileDrawX,tileDrawY };
		sampleTileDraw.imageName = L"샘플타일";
		//sampleTileDraw.atlasInfo.frameSize = { tileDrawX,tileDrawY };
		//sampleTileDraw.atlasInfo.frame = { 0,0 };
		sampleTileDraw.atlasInfo.isCostumAtlas = true;
		sampleTileDraw.atlasInfo.costumAtlasSize = { 0.0f,0.0f,(float)tileDrawX ,(float)tileDrawY };
		sampleTileDraw.imageLocation = { (float)WINSIZE_TILE_MAP_X - (tileDrawX/2) , (float)samlpeTileRect.top + tileDrawY / 2 };
		sampleTileDraw.imageEffect = D2DIE_ATLAS;
		

			// 오른쪽 상단에 메인 타일의 정보를 셋팅
		for (int i = 0; i < sample_Tile_Y; i++)
		{
			for (int j = 0; j < sample_Tile_X; j++)
			{
				SetRect(&samlpeTile[i * sample_Tile_X + j].rc,
											samlpeTileRect.left +  j * tile_Size.cx ,			 i * tile_Size.cy ,
											samlpeTileRect.left +  (j + 1) * tile_Size.cx ,	(i + 1) * tile_Size.cy );

				samlpeTile[i * sample_Tile_X + j].frameX = j;
				samlpeTile[i * sample_Tile_X + j].frameY = i;
			}
		}
	}
	else
	{
		//isSpamlpeTileOver = false;
		//sampleTileDraw.DrawRectSetting("maptiles", { (float)samlpeTileRect.left + 640 / 2  , (float)samlpeTileRect.top + 288 / 2 }, { 640,288 });
		//	// 오른쪽 상단에 메인 타일의 정보를 셋팅
		//for (int i = 0; i < sample_Tile_Y; i++)
		//{
		//	for (int j = 0; j < sample_Tile_X; j++)
		//	{
		//		SetRect(&samlpeTile[i * sample_Tile_X + j].rc,
		//									WINSIZE_TILE_MAP_X - sampleTile->GetImageInfo()->width +  j * tile_Size.cx ,			 i * tile_Size.cy ,
		//									WINSIZE_TILE_MAP_X - sampleTile->GetImageInfo()->width +  (j + 1) * tile_Size.cx ,	(i + 1) * tile_Size.cy );

		//		samlpeTile[i * sample_Tile_X + j].frameX = j;
		//		samlpeTile[i * sample_Tile_X + j].frameY = i;
		//	}
		//}
	}
	selectTile.frameX = defaultFrame;
	selectTile.frameY = defaultFrame;
	// 세이브 로드 버튼
	rcSave = { samlpeTileRect.left  , samlpeTileRect.bottom + 250 ,
				 samlpeTileRect.left + 150 ,samlpeTileRect.bottom + 320 };

	rcLoad = { samlpeTileRect.left + 160, samlpeTileRect.bottom + 250 ,
				 samlpeTileRect.left + 310 ,samlpeTileRect.bottom + 320 };
	rcExit = { WINSIZE_TILE_MAP_X - 200, WINSIZE_TILE_MAP_Y - 100, 
				WINSIZE_TILE_MAP_X - 59,  WINSIZE_TILE_MAP_Y - 45 };

	rcLayerLoad = rcLoad;
	rcLayerLoad.left += 160;
	rcLayerLoad.right = rcLayerLoad.left + 150;

	saveButtoninfo.imageName = L"버튼";
	saveButtoninfo.imageLocation = { (float)rcSave.left + 143 / 2, (float)rcSave.top + 35 };
	saveButtoninfo.atlasInfo.frameSize = { 143,57 };
	saveButtoninfo.atlasInfo.frame = { 1,0 };
	saveButtoninfo.imageEffect = D2DIE_ATLAS;

	loadButtoninfo = saveButtoninfo;
	loadButtoninfo.imageLocation = { (float)rcLoad.left + 143 / 2, (float)rcLoad.top + 35 };
	loadButtoninfo.atlasInfo.frame.x = 0;


	layerLoadButtoninfo = saveButtoninfo;
	layerLoadButtoninfo.imageLocation = { (float)rcLayerLoad.left + 143 / 2, (float)rcLayerLoad.top + 35 };
	layerLoadButtoninfo.atlasInfo.frame.x = 0;


	exitButtoninfo.imageName = L"탈출";
	exitButtoninfo.imageLocation = { (float)rcExit.left + 141 / 2, (float)rcExit.top +55/2};
	exitButtoninfo.atlasInfo.frameSize = { 141,55 };
	exitButtoninfo.atlasInfo.frame = { 0,0 };
	exitButtoninfo.imageEffect = D2DIE_ATLAS;

	rcSizeX = { samlpeTileRect.left + 10  , samlpeTileRect.bottom + 150 ,
				 samlpeTileRect.left + 60 ,samlpeTileRect.bottom + 200 };

	rcSizeY = { samlpeTileRect.left + 80, samlpeTileRect.bottom + 150 ,
				 samlpeTileRect.left + 130 ,samlpeTileRect.bottom + 200 };

	rcOkButton = { samlpeTileRect.left + 150, samlpeTileRect.bottom + 150 ,
					   samlpeTileRect.left + 200 ,samlpeTileRect.bottom + 200 };


	// 왼쪽 상단에 메인 타일의 정보를 셋팅
	for (int i = 0; (UINT)i < tile_Y; i++)
	{
		for (int j = 0; (UINT)j < tile_X; j++)
		{
			SetRect(&tiles[i * tile_X + j].rc,
							 j * tile_Size.cx,		 i * tile_Size.cy + renderOffset,
							(j + 1) * tile_Size.cx,	(i + 1) * tile_Size.cy + renderOffset);

			tiles[i * tile_X + j].terrain = TERRAIN::GRASS;
			tiles[i * tile_X + j].frameX = defaultFrame;
			tiles[i * tile_X + j].frameY = defaultFrame;
			tiles[i * tile_X + j].rotation = 0.0f;
			tiles[i * tile_X + j].geometryinfo.ReSet();
		}
	}
	TilesDrawinfo.imageName = L"샘플타일";
	TilesDrawinfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE | D2DIE_SCALE;
	TilesDrawinfo.atlasInfo.frameSize = { (float)SelectTile_Size.cx ,(float)SelectTile_Size.cy };
	TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(0, {0,0});
	TilesDrawinfo.scaleInfo.scaleCenterPoint = { (float)SelectTile_Size.cx / 2 , (float)SelectTile_Size.cy / 2 };
	TilesDrawinfo.scaleInfo.scaleSize = { 2.0f,2.0f };

	selectDrawinfo.imageName = L"샘플타일";
	selectDrawinfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE | D2DIE_SCALE;;
	selectDrawinfo.imageLocation = { (float)WINSIZE_TILE_MAP_X - (sampleTileSize.width) + tile_Size.cy / 2, (sampleTileSize.height + 100) };
	selectDrawinfo.atlasInfo.frameSize = { (float)SelectTile_Size.cx ,(float)SelectTile_Size.cy };
	selectDrawinfo.atlasInfo.frame.x = selectTile.frameX;
	selectDrawinfo.atlasInfo.frame.y = selectTile.frameY;
	selectDrawinfo.scaleInfo.scaleCenterPoint = { (float)SelectTile_Size.cx / 2 , (float)SelectTile_Size.cy / 2 };
	selectDrawinfo.scaleInfo.scaleSize = { 2.0f,2.0f };
	imageManager->ImageRander(selectDrawinfo);
	// 5분마다 자동 저장
	TimerManager::GetSingleton()->SetTimer(autoSaveTimerHandle,this,&TileMapToolScene::AutoSave, 300.0f);

	isSelectTileRender = false;
	isRectDraw = false;
	isCollisionLayer = true;
	sizeKind = SizeKind::None;
	SetGeometry(GeometryKinds::Triangle);
	numCount = 0;
	temptile_X = tile_X;
	temptile_Y = tile_Y;
	autoSaveCount = 0;
	okButtonColor = OK_BUTTON_DEFAULT_COLOR;
	isOpen = false;
	IsGridline = true;
	layerTile = nullptr;
	isLayerTileRender = false;
	return S_OK;
}

void TileMapToolScene::Release()
{
	// 맵툴이 끝났음으로 실제 게임 사이즈로 조정
	SetWindowSize(0, 0, WINSIZE_X, WINSIZE_Y);
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	D2D::GetSingleton()->GetD2DRenderTarget()->Resize({ (UINT32)rect.right, (UINT32)rect.bottom });
	geometry->Release();

}

void TileMapToolScene::Update()
{
	isSelectTileRender = false;
	RECT samplerc = { samlpeTileRect.left  , 0 , WINSIZE_TILE_MAP_X ,tileDrawY };
	RECT tilerc;
	if (isTileOver)
		tilerc = { 0  , (LONG)renderOffset  , (LONG)tile_Render_X * tile_Size.cx , (LONG)tile_Render_Y * tile_Size.cy + (LONG)renderOffset };
	else
		tilerc = { 0  , 0 , (LONG)tile_X * tile_Size.cx , (LONG)tile_Y * tile_Size.cy };

	KeyManager* key = KeyManager::GetSingleton();
	


	if ((key->IsStayKeyDown(VK_CONTROL)))
	{
		if (key->IsOnceKeyDown(VK_DELETE))
			this->DeleteLayer();
		// 레이어 토글
		if (key->IsOnceKeyDown(_1Key))
			isLayerTileRender = !isLayerTileRender;
		if (key->IsOnceKeyDown(ZKey))
			this->Undo();
		// 격자눈 토글
		if (key->IsOnceKeyDown(VK_TAB))
			IsGridline = !IsGridline;

		if (key->IsStayKeyDown(VK_SHIFT))
		{
			if (key->IsOnceKeyDown(SKey))
			{
				DEBUG_MASSAGE("퀵 세이브\n");
				QuickSave();

			}
		}

		// 타일 이동
		// 세밀 조정
		// 샘플 타일 이동
		if (key->IsOnceKeyDown(VK_LEFT))
			this->SampleTileMoveSide(true);
		else if (key->IsOnceKeyDown(VK_RIGHT))
			this->SampleTileMoveSide(false);

		if (key->IsOnceKeyDown(VK_UP))
			this->SampleTileMoveUp(true);
		else if (key->IsOnceKeyDown(VK_DOWN))
			this->SampleTileMoveUp(false);

		// 세밀 조정
		// 타이틀맵 이동
		if (key->IsOnceKeyDown(AKey))
			this->TileMoveSide(true);
		else if (key->IsOnceKeyDown(DKey))
			this->TileMoveSide(false);

		if (key->IsOnceKeyDown(WKey))
			this->TileMoveUp(true);
		else if (key->IsOnceKeyDown(SKey))
			this->TileMoveUp(false);
	}
	else
	{

		if (key->IsStayKeyDown(VK_SHIFT))
		{
			if (key->IsOnceKeyDown(WKey))
				this->TileIndexMoveUP(true);
			else if (key->IsOnceKeyDown(SKey))
				this->TileIndexMoveUP(false);

			if (key->IsOnceKeyDown(AKey))
				this->TileIndexMoveSide(true);
			else if (key->IsOnceKeyDown(DKey))
				this->TileIndexMoveSide(false);
		}
		else
		{

			if (key->IsStayKeyDown(VK_LEFT))
				this->SampleTileMoveSide(true);
			else if (key->IsStayKeyDown(VK_RIGHT))
				this->SampleTileMoveSide(false);

			if (key->IsStayKeyDown(VK_UP))
				this->SampleTileMoveUp(true);
			else if (key->IsStayKeyDown(VK_DOWN))
				this->SampleTileMoveUp(false);


			// 타이틀맵 이동
			if (key->IsStayKeyDown(AKey))
				this->TileMoveSide(true);
			else if (key->IsStayKeyDown(DKey))
				this->TileMoveSide(false);

			if (key->IsStayKeyDown(WKey))
				this->TileMoveUp(true);
			else if (key->IsStayKeyDown(SKey))
				this->TileMoveUp(false);
		}
	}
	// 콜리전  토글 
	if (key->IsOnceKeyDown(VK_TAB))
		isCollisionLayer = !isCollisionLayer;
		
	if (PtInRect(&samplerc, g_ptMouse))
	{
		if (key->IsOnceKeyDown(VK_LBUTTON))
		{
			this->RectSelectBegin();
		}
		if (key->IsOnceKeyUP(VK_LBUTTON))
		{
			this->RectSelectEnd(samplerc);
		}
	}
	else if (PtInRect(&tilerc, g_ptMouse))
	{
		isSelectTileRender = true;
		// Alt키
		if (key->IsStayKeyDown(VK_MENU))
		{
			if (key->IsStayKeyDown(VK_LBUTTON) || key->IsStayKeyDown(VK_RBUTTON))
				this->Dropper(tilerc);
		}
		else
		{
			if (key->IsStayKeyDown(VK_RBUTTON))
				this->Erase(tilerc);

			if (key->IsStayKeyDown(VK_SHIFT))
			{
				if (key->IsOnceKeyDown(VK_LBUTTON))
				{
					this->RectDrawBegin();
					isRectDraw = true;
				}
				if (isRectDraw)
				{
					this->RectDrawMove();
					if (key->IsOnceKeyUP(VK_LBUTTON))
					{
						this->RectDrawEnd(tilerc);
						isRectDraw = false;
					}
				}
			}
			else
			{
				isRectDraw = false;
				if (key->IsStayKeyDown(VK_CONTROL))
				{
					if (key->IsOnceKeyDown(VK_LBUTTON))
						this->Draw(tilerc);
				}
				else
				{
					if (key->IsStayKeyDown(VK_LBUTTON))
						this->Draw(tilerc);
				}
			}
		}
	}
	if (key->IsOnceKeyDown(VK_DELETE))
		this->CleanAll();
	if (key->IsOnceKeyDown(QKey))
	{
		if (isCollisionLayer)
		{
			geometryinfo.rotation -= 90.0f;
			if (geometryinfo.rotation < 0)
				geometryinfo.rotation += 360.0f;
		}
		else
		{
			for (size_t i = 0; i < selectTiles.size(); i++)
			{
				selectTiles[i].rotation -= 90.0f;
				if (selectTiles[i].rotation < 0)
					selectTiles[i].rotation += 360.0f;
			}
		}
	}
	if (key->IsOnceKeyDown(EKey))
	{
		if (isCollisionLayer)
		{
			geometryinfo.rotation += 90.0f;
			if (geometryinfo.rotation > 360.0f)
				geometryinfo.rotation += 360.0f;
		}
		else
		{
			for (size_t i = 0; i < selectTiles.size(); i++)
			{
				selectTiles[i].rotation += 90.0f;
				if (selectTiles[i].rotation > 360.0f)
					selectTiles[i].rotation -= 360.0f;
			}
		}
	}
	if (key->IsOnceKeyDown(RKey))
	{
		if (isCollisionLayer)
			geometryinfo.isRevers = !geometryinfo.isRevers;
		else
		{
			for (size_t i = 0; i < selectTiles.size(); i++)
			{
				selectTiles[i].isReverse = !selectTiles[i].isReverse;
			}
		}
	}

	// 기하학 정보 키입력
	GeometryInfoKeyInput();
	// 세이브 로드
	if (PtInRect(&rcSave, g_ptMouse))
	{
		saveButtoninfo.atlasInfo.frame.y = 1;
		if (key->IsOnceKeyUP(VK_LBUTTON))
			this->Save();
	}
	else
		saveButtoninfo.atlasInfo.frame.y = 0;

	if (PtInRect(&rcLoad, g_ptMouse))
	{
		loadButtoninfo.atlasInfo.frame.y = 1;
		if (key->IsOnceKeyUP(VK_LBUTTON))
			this->Load();
	}
	else
		loadButtoninfo.atlasInfo.frame.y = 0;

	// 탈출 버튼
	if (PtInRect(&rcExit, g_ptMouse))
	{
		// 난중에 추가
		exitButtoninfo.atlasInfo.frame.y = 1;
	}
	else
		exitButtoninfo.atlasInfo.frame.y = 0;

	if (PtInRect(&rcLayerLoad, g_ptMouse))
	{
		layerLoadButtoninfo.atlasInfo.frame.y = 1;
		if (key->IsOnceKeyUP(VK_LBUTTON))
			this->LayerLoad();
	}
	else
		layerLoadButtoninfo.atlasInfo.frame.y = 0;
	// 사이즈 조정
	if (PtInRect(&rcSizeX, g_ptMouse))
	{
		HCURSOR cursor = LoadCursor(NULL, IDC_IBEAM);
		SetCursor(cursor);
		if (key->IsOnceKeyUP(VK_LBUTTON))
		{
			sizeKind = SizeKind::X;
			numCount = 0;
			temptile_X = 0;
		}
	}

	if (PtInRect(&rcSizeY, g_ptMouse))
	{
		HCURSOR cursor = LoadCursor(NULL, IDC_IBEAM);
		SetCursor(cursor);
		if (key->IsOnceKeyUP(VK_LBUTTON))
		{
			sizeKind = SizeKind::Y;
			numCount = 0;
			temptile_Y = 0;
		}
	}

	if (PtInRect(&rcOkButton, g_ptMouse))
	{
		okButtonColor = OK_BUTTON_SELECT_COLOR;
		if (key->IsOnceKeyUP(VK_LBUTTON))
		{
			sizeKind = SizeKind::None;
			if (temptile_X < tile_Render_X)
				temptile_X = tile_Render_X;
			if (temptile_Y < tile_Render_Y)
				temptile_Y = tile_Render_Y;
			Resize(temptile_X, temptile_Y);
		}
	}
	else
		okButtonColor = OK_BUTTON_DEFAULT_COLOR;

	if (sizeKind != SizeKind::None)
	{
		switch (sizeKind)
		{
		case SizeKind::X:
			NumberKeyInput(true);
			break;
		case SizeKind::Y:
			NumberKeyInput(false);
			break;
		}

	}
}

void TileMapToolScene::Render()
{

	D2D* d2d = D2D::GetSingleton();
	ID2D1HwndRenderTarget* renderTarget = d2d->GetD2DRenderTarget();
	brush = d2d->GetBrush();
	brush->SetColor(D2D1::ColorF(0xffffff,0.0f));
	renderTarget->FillRectangle({0,0,(float)(tile_X * tile_Size.cx), (float)(tile_Y * tile_Size.cy )}, brush);
	
	D2D1_SIZE_U testsit = renderTarget->GetPixelSize();


	ImageManager* imageManager = IMAGEMANAGER;
	imageManager->ImageRander(sampleTileDraw);

	
	// 타일 정보

	UINT tileRenderSize = tile_Y * tile_X;
	if (!isTileOver)
	{
		for (int i = 0; (UINT)i < (tile_Y * tile_X); i++)
		{
			TilesDrawinfo.imageLocation = { (float)tiles[i].rc.left + tile_Size.cx / 2,(float)tiles[i].rc.top + tile_Size.cy / 2 };
			TilesDrawinfo.atlasInfo.frame.x = tiles[i].frameX;
			TilesDrawinfo.atlasInfo.frame.y = tiles[i].frameY;
			imageManager->ImageRander(TilesDrawinfo);

		}
		// 격자 선
		brush->SetColor(D2D1::ColorF(0xffffff));
		for (int i = 0; (UINT)i < tile_Y * tile_X; i++)
			renderTarget->DrawRectangle({ (float)tiles[i].rc.left, (float)tiles[i].rc.top, (float)tiles[i].rc.right, (float)tiles[i].rc.bottom }, brush);
		
	}
	// 타일 오버 시
	else
	{
		RECT tilerc;
		int index = 0;
		for (int i = 0; i < tile_Render_Y; i++)
		{
			for (int j = 0; j < tile_Render_X; j++)
			{
				index = (tile_X * (i + tileCamePos.y)) + (j + tileCamePos.x);
				if (!tiles[index].GetisRender())
					continue;
				tilerc = tiles[(tile_X * i) + j].rc;
				TilesDrawinfo.imageLocation = { (float)tilerc.left + tile_Size.cx / 2,(float)tilerc.top + tile_Size.cy / 2 };
				TilesDrawinfo.atlasInfo.frame.x = tiles[index].frameX;
				TilesDrawinfo.atlasInfo.frame.y = tiles[index].frameY;
				if (tiles[index].isReverse)
					TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(tiles[index].rotation, { (float)SelectTile_Size.cx / 2, (float)SelectTile_Size.cy / 2 }) * Matrix3x2F::Scale({ -1.0f,1.0f }, { (float)SelectTile_Size.cx / 2, (float)SelectTile_Size.cy / 2 });
				else
					TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(tiles[index].rotation, { (float)SelectTile_Size.cx / 2, (float)SelectTile_Size.cy / 2 });
				imageManager->ImageRander(TilesDrawinfo);
			}
		}
		// 격자 선
		brush->SetColor(D2D1::ColorF(0xffffff));
		if (IsGridline)
		{
			for (int i = 0; i < tile_Render_Y; i++)
			{
				for (int j = 0; j < tile_Render_X; j++)
				{
					index = (tile_X * i) + j;
					tilerc = tiles[index].rc;
					renderTarget->DrawRectangle({ (float)tilerc.left, (float)tilerc.top, (float)tilerc.right, (float)tilerc.bottom }, brush);
				}
			}
		}
	}

	this->LayerTileRender();

	if (isCollisionLayer)
	{	
		// 무조건 삭제후 생성???
		d2d->GetD2DFactory()->CreatePathGeometry(&geometry);
		GetGeomrtyPoint(geometryinfo);
		brush->SetColor(ColorF(1.0f, 1.0f, 1.0f, 0.7f));
		renderTarget->FillGeometry(geometry, brush);
		geometry->Release();
		UINT32 segmentCount =0;
		int index;
		for (int i = 0; i < tile_Render_Y; i++)
		{
			for (int j = 0; j < tile_Render_X; j++)
			{
				index = (tile_X * (i + tileCamePos.y)) + (j + tileCamePos.x);
				if (tilesgeometry[index])
				{
					tilesgeometry[index]->GetSegmentCount(&segmentCount);
					// 세팅된것만 실행
					if (segmentCount > 0)
						renderTarget->FillGeometry(tilesgeometry[index], brush);
				}
			}
		}
	}
	else
	//
	{
		Matrix3x2F scale;
		if (isSelectTileRender)
			selectDrawinfo.scaleInfo.scaleSize = { 2.0f,2.0f };
		else
			selectDrawinfo.scaleInfo.scaleSize = { 1.0f,1.0f };
		if (selectTiles.size() != 0)
		{
			int count = 0;
			float x, y;
			for (int i = 0; i < selectSize.cy; i++)
			{
				for (int j = 0; j < selectSize.cx; j++)
				{
					x = (float)g_ptMouse.x + (j * tile_Size.cx);
					y = (float)g_ptMouse.y + (i * tile_Size.cy);
					//if (x > (float)(tile_Size.cx * tile_X))
					//{
					//	count++;
					//	continue;
					//}
					//if (x > (float)(tile_Size.cy * tile_Y))
					//{
					//	count++;
					//	continue;
					//}
					if (isSelectTileRender)
						selectDrawinfo.imageLocation = { (float)g_ptMouse.x + (j * (tile_Size.cx-1)), (float)g_ptMouse.y + (i * (tile_Size.cy-1)) };
					else
						selectDrawinfo.imageLocation = { (float)g_ptMouse.x + (j * SelectTile_Size.cx), (float)g_ptMouse.y + (i * SelectTile_Size.cy) };

					if (selectTiles[count].isReverse)
						scale = Matrix3x2F::Scale({ -1.0f,1.0f }, { 16.0f,16.0f });
					else
						scale = Matrix3x2F::Scale({ 1.0f,1.0f });
					selectDrawinfo.atlasInfo.frame.x = selectTiles[count].frameX;
					selectDrawinfo.atlasInfo.frame.y = selectTiles[count].frameY;
					selectDrawinfo.affineMatrix = Matrix3x2F::Rotation(selectTiles[count++].rotation, { 16.0f,16.0f }) * scale;
					imageManager->ImageRander(selectDrawinfo);
				}
			}
		}
		
	}


	// 세이브 로드
	imageManager->ImageRander(saveButtoninfo);
	imageManager->ImageRander(loadButtoninfo);
	imageManager->ImageRander(layerLoadButtoninfo);
	imageManager->ImageRander(exitButtoninfo);
	//layerLoadButtoninfo
	ID2D1SolidColorBrush* fontBrush = d2d->GetTextBrush();
	brush->SetColor(ColorF({ 1.0f,1.0f,1.0f }));
	fontBrush->SetColor(ColorF({ 1.0f,1.0f,1.0f }));

	//renderTarget->FillRectangle({ (float)rcLayerLoad.left, (float)rcLayerLoad.top - 30, (float)rcLayerLoad.right, (float)rcLayerLoad.top }, brush);
	d2d->__DrawText(L"레이어 불러오기", { (float)rcLayerLoad.left, (float)rcLayerLoad.top - 30, (float)rcLayerLoad.right, (float)rcLayerLoad.top });
	d2d->__DrawText(L"불러오기", { (float)rcLoad.left - 1.5f, (float)rcLoad.top - 30, (float)rcLoad.right - 1.5f, (float)rcLoad.top });
	d2d->__DrawText(L"저장하기", { (float)rcSave.left, (float)rcSave.top - 30, (float)rcSave.right, (float)rcSave.top });
	d2d->__DrawText(L"X", { (float)rcSizeX.left, (float)rcSizeX.top - 30, (float)rcSizeX.right, (float)rcSizeX.top });
	d2d->__DrawText(L"Y", { (float)rcSizeY.left, (float)rcSizeY.top - 30, (float)rcSizeY.right, (float)rcSizeY.top });
	fontBrush->SetColor(ColorF({ 0.0f,0.0f,0.0f }));
	// 사이즈 조정 박스 
	wstring X = to_wstring(temptile_X);
	renderTarget->FillRectangle({ (float)rcSizeX.left, (float)rcSizeX.top, (float)rcSizeX.right, (float)rcSizeX.bottom }, brush);
	d2d->__DrawText(X.c_str(), { (float)rcSizeX.left, (float)rcSizeX.top, (float)rcSizeX.right, (float)rcSizeX.bottom });

	wstring Y = to_wstring(temptile_Y);
	renderTarget->FillRectangle({ (float)rcSizeY.left, (float)rcSizeY.top, (float)rcSizeY.right, (float)rcSizeY.bottom }, brush);
	d2d->__DrawText(Y.c_str(), { (float)rcSizeY.left, (float)rcSizeY.top, (float)rcSizeY.right, (float)rcSizeY.bottom });

	brush->SetColor(okButtonColor.GetColor());
	renderTarget->FillRectangle({ (float)rcOkButton.left, (float)rcOkButton.top, (float)rcOkButton.right, (float)rcOkButton.bottom }, brush);
	d2d->__DrawText(L"적용", { (float)rcOkButton.left, (float)rcOkButton.top, (float)rcOkButton.right, (float)rcOkButton.bottom });
	fontBrush->SetColor(ColorF({ 1.0f,1.0f,1.0f }));

	wstring Xoffset = L"Left : " + to_wstring(tileCamePos.x);
	d2d->__DrawText(Xoffset.c_str(), { (float)rcSizeX.left, (float)rcSizeX.top - 120, (float)rcSizeX.right + 100, (float)rcSizeX.bottom - 120});

	wstring Yoffset = L"Top  : " + to_wstring(tileCamePos.y);
	d2d->__DrawText(Yoffset.c_str(), { (float)rcSizeX.left, (float)rcSizeX.top - 100, (float)rcSizeX.right + 100, (float)rcSizeX.bottom - 100 });

	wstring Showoffset = L"Show  : " + to_wstring(tile_Render_X);
	d2d->__DrawText(Showoffset.c_str(), { (float)rcSizeX.left, (float)rcSizeX.top - 80, (float)rcSizeX.right + 100, (float)rcSizeX.bottom - 80 });


#pragma region 기하학 충돌 테스트 용 메모 추후에 제거할것
	//기하학 충돌 테스트
	//static int test;
	//ID2D1PathGeometry* mp_path_geometry = NULL;
	////mp_path_geometry->CompareWithGeometry(,,);
	//D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&mp_path_geometry);
	//D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = D2D1::StrokeStyleProperties(
	//	D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_TRIANGLE,
	//	D2D1_LINE_JOIN_MITER, 10.0f,
	//	D2D1_DASH_STYLE_SOLID, 0.0f);

	//ID2D1StrokeStyle* mp_stroke_style = NULL;
	//D2D::GetSingleton()->GetD2DFactory()->CreateStrokeStyle(strokeStyleProperties, NULL, 0, &mp_stroke_style);



	//// 경로 기하에 조각들을 기록하기 위해서 기하 싱크를 얻음.
	//ID2D1GeometrySink* mp_sink = NULL;
	//mp_path_geometry->Open(&mp_sink);

	//// 피겨의 시작.(피겨의 시작점, 채우기 or 비우기)
	//mp_sink->BeginFigure(D2D1::Point2F(700, 700), D2D1_FIGURE_BEGIN_FILLED);
	//// 조각 추가.
	//D2D1_POINT_2F points[3] = { D2D1::Point2F(700, 800), D2D1::Point2F(800, 800), D2D1::Point2F(800, 700) };
	//mp_sink->AddLines(points, 3);
	//// 피겨의 끝.
	//mp_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	//mp_sink->Close();
	////D2D1_GEOMETRY_RELATION_DISJOINT

	//mp_path_geometry2 = NULL;
	////mp_path_geometry->CompareWithGeometry(,,);
	//D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&mp_path_geometry2);

	//// 경로 기하에 조각들을 기록하기 위해서 기하 싱크를 얻음.
	//ID2D1GeometrySink* mp_sink2 = NULL;
	//mp_path_geometry2->Open(&mp_sink2);

	//// 피겨의 시작.(피겨의 시작점, 채우기 or 비우기)
	//mp_sink2->BeginFigure(D2D1::Point2F((float)g_ptMouse.x, (float)g_ptMouse.y), D2D1_FIGURE_BEGIN_FILLED);
	//// 조각 추가.
	//D2D1_POINT_2F points2[2] = { D2D1::Point2F((float)g_ptMouse.x , (float)g_ptMouse.y + 110), D2D1::Point2F((float)g_ptMouse.x +80, (float)g_ptMouse.y+110 )};
	//mp_sink2->AddLines(points2, 2);
	//// 피겨의 끝.
	//mp_sink2->EndFigure(D2D1_FIGURE_END_CLOSED);
	//mp_sink2->Close();
	//
	//ID2D1PathGeometry* mp_path_geometry3 = NULL;
	////mp_path_geometry->CompareWithGeometry(,,);
	//D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&mp_path_geometry3);

	//// 경로 기하에 조각들을 기록하기 위해서 기하 싱크를 얻음.
	//ID2D1GeometrySink* mp_sink3 = NULL;
	//mp_path_geometry3->Open(&mp_sink3);

	//// 피겨의 시작.(피겨의 시작점, 채우기 or 비우기)
	//mp_sink3->BeginFigure(D2D1::Point2F((float)0, (float)0), D2D1_FIGURE_BEGIN_FILLED);
	//// 조각 추가.
	//D2D1_POINT_2F points3[2] = { D2D1::Point2F(0,110), D2D1::Point2F((float) 80, (float)110) };
	//mp_sink3->AddLines(points3, 2);
	//// 피겨의 끝.
	//mp_sink3->EndFigure(D2D1_FIGURE_END_CLOSED);
	//mp_sink3->Close();



	//D2D1_GEOMETRY_RELATION theRelation;
	////for (int i = 0; i < 3000 ;i++)
	//mp_path_geometry->CompareWithGeometry(mp_path_geometry3, Matrix3x2F::Translation((float)g_ptMouse.x, (float)g_ptMouse.y), &theRelation);

	//switch (theRelation)
	//{
	//case D2D1_GEOMETRY_RELATION_UNKNOWN:
	//	break;
	//case D2D1_GEOMETRY_RELATION_DISJOINT:
	//	DEBUG_MASSAGE("안곂침");
	//	break;
	//case D2D1_GEOMETRY_RELATION_IS_CONTAINED:
	//	DEBUG_MASSAGE("대상이 더큰 포함");
	//	break;
	//case D2D1_GEOMETRY_RELATION_CONTAINS:
	//	DEBUG_MASSAGE("대상이 작은 포함");
	//	break;
	//case D2D1_GEOMETRY_RELATION_OVERLAP:
	//	DEBUG_MASSAGE("곂침");
	//	break;
	//case D2D1_GEOMETRY_RELATION_FORCE_DWORD:
	//	break;
	//default:
	//	break;
	//}
	////test++;
	//// 렌더타겟에 경로 기하 그리기.
	//brush->SetColor(D2D1::ColorF(0xffffff));

	//D2D::GetSingleton()->GetD2DRenderTarget()->DrawGeometry(mp_path_geometry, brush, 1.f, mp_stroke_style);
	//D2D::GetSingleton()->GetD2DRenderTarget()->FillGeometry(mp_path_geometry2, brush);

	//mp_path_geometry->Release();
	//mp_sink->Release();
	//mp_stroke_style->Release();

#pragma endregion
}

void TileMapToolScene::LayerTileRender()
{
	if (isLayerTileRender)
	{
		if (layerTile)
		{
			RECT tilerc;
			int index = 0;
			for (int i = 0; i < tile_Render_Y; i++)
			{
				if (layerTile->tile_Y <= (UINT)(i + tileCamePos.y))
					break;
				for (int j = 0; j < tile_Render_X; j++)
				{
					if (layerTile->tile_X <= (UINT)(j + tileCamePos.x))
						break;
					index = (layerTile->tile_X * (i + tileCamePos.y)) + (j + tileCamePos.x);
					if (!layerTile->tiles[index].GetisRender())
						continue;
					tilerc = tiles[(tile_X * i) + j].rc;
					TilesDrawinfo.imageLocation = { (float)tilerc.left + tile_Size.cx / 2,(float)tilerc.top + tile_Size.cy / 2 };
					TilesDrawinfo.atlasInfo.frame.x = layerTile->tiles[index].frameX;
					TilesDrawinfo.atlasInfo.frame.y = layerTile->tiles[index].frameY;
					//if (layerTile->tiles[index].rotation != 0.0f)
					TilesDrawinfo.affineMatrix = Matrix3x2F::Rotation(layerTile->tiles[index].rotation, { (float)SelectTile_Size.cx / 2, (float)SelectTile_Size.cy / 2 });
					IMAGEMANAGER->ImageRander(TilesDrawinfo);
				}
			}
		}
	}
}

void TileMapToolScene::Select(const RECT& samlpeRc)
{
	int posx = g_ptMouse.x - samlpeRc.left, posy = g_ptMouse.y - samlpeRc.top;
	int indexX = posx / tile_Size.cx;
	int indexY = posy / tile_Size.cy;

	selectTile.frameX = samlpeTile[indexY * sample_Tile_X + indexX].frameX;
	selectTile.frameY = samlpeTile[indexY * sample_Tile_X + indexX].frameY;
}

void TileMapToolScene::RectSelectBegin()
{
	rectSelect.left = g_ptMouse.x;
	rectSelect.top = g_ptMouse.y;
}

void TileMapToolScene::RectSelectEnd(const RECT & samlpeRc)
{
	if (isCollisionLayer)
		return;
	selectTiles.clear();
	rectSelect.right = g_ptMouse.x;
	rectSelect.bottom = g_ptMouse.y;
	int posx = rectSelect.left - samlpeRc.left, posy = rectSelect.top - samlpeRc.top;
	int LindexX = posx / SelectTile_Size.cx + (samlpeTileMovepos.x / SelectTile_Size.cx);
	int LindexY = posy / SelectTile_Size.cy + (samlpeTileMovepos.y / SelectTile_Size.cy);

	posx = rectSelect.right - samlpeRc.left;
	posy = rectSelect.bottom - samlpeRc.top;

	int RindexX = posx / SelectTile_Size.cx + (samlpeTileMovepos.x / SelectTile_Size.cx);
	int RindexY = posy / SelectTile_Size.cy + (samlpeTileMovepos.y / SelectTile_Size.cy);

	SelectTile buffer;
	selectSize.cx =  RindexX - LindexX + 1;
	selectSize.cy = RindexY - LindexY + 1;
	for (int i = LindexY; i <= RindexY; i++)
	{
		for (int j = LindexX; j <= RindexX; j++)
		{
			buffer.frameX =  samlpeTile[i * sample_Tile_X + j].frameX;// = selectTile.frameX;
			buffer.frameY = samlpeTile[i * sample_Tile_X + j].frameY;// = selectTile.frameY;
			buffer.rotation = 0.0f;
			selectTiles.push_back(buffer);
		}
	}
	if (!selectTiles.empty())
		selectTile = selectTiles[0];
}

void TileMapToolScene::Draw(const RECT& tileRc)
{
	int posx = g_ptMouse.x - tileRc.left, posy = g_ptMouse.y - tileRc.top;
	int indexX = posx / tile_Size.cx;
	int indexY = posy / tile_Size.cy;

	if (isCollisionLayer)
	{
		int yMax = min(tile_Render_X, selectSize.cy + indexY);
		int xMax = min(tile_Render_Y, selectSize.cx + indexX);
		int count = 0;
		int index = 0;

		index = ((indexY + tileCamePos.y) * tile_X + (indexX + tileCamePos.x));
		if (tiles[index].geometryinfo == geometryinfo)
			return;
		WorklistAdd();
		tiles[index].geometryinfo = geometryinfo;
		if (tilesgeometry[index])
			tilesgeometry[index]->Release();
		D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&tilesgeometry[index]);
		GetGeomrtyPoint(tilesgeometry[index], tiles[index].geometryinfo, tiles[((indexY) * tile_X + (indexX))].rc);
		WorklistAdd();
		return;
	}

	bool isWorldAdd = false;
	if (!isTileOver)
	{
		int yMax = min(tile_Y, (UINT)selectSize.cy + indexY);
		int xMax = min(tile_X, (UINT)selectSize.cx + indexX);
		int count = 0;
		for (int i = indexY; i < yMax; i++)
		{
			for (int j = indexX; j < xMax; j++)
			{
				tiles[i * tile_X + j].frameX = selectTiles[count].frameX;
				tiles[i * tile_X + j].frameY = selectTiles[count].frameX;
				tiles[i * tile_X + j].rotation = selectTiles[count].rotation;
				tiles[i * tile_X + j].isReverse = selectTiles[count++].rotation;
			}
		}
	}
	// 드로우 타일 보정 
	else
	{
		int yMax = min(tile_Render_Y, selectSize.cy + indexY);
		int xMax = min(tile_Render_X, selectSize.cx + indexX);
		int count = 0;
		int index = 0;
		for (int i = indexY; i < yMax; i++)
		{
			for (int j = indexX; j < xMax; j++)
			{
				index = ((i + tileCamePos.y) * tile_X + (j + tileCamePos.x));
				if ((tiles[index].frameX != selectTiles[count].frameX) |
					(tiles[index].frameY != selectTiles[count].frameY) |
					(tiles[index].rotation != selectTiles[count].rotation))
					if (!isWorldAdd)
					{
						isWorldAdd = true;
						WorklistAdd();
					}
				tiles[index].frameX = selectTiles[count].frameX;
				tiles[index].frameY = selectTiles[count].frameY;
				tiles[index].rotation = selectTiles[count].rotation;
				tiles[index].isReverse = selectTiles[count++].isReverse;
				
			}
		}
	}
}

void TileMapToolScene::RectDrawBegin()
{
	rectDraw.left = g_ptMouse.x;
	rectDraw.top = g_ptMouse.y;
}

void TileMapToolScene::RectDrawMove()
{
	rectDraw.right = g_ptMouse.x;
	rectDraw.bottom = g_ptMouse.y;
}

void TileMapToolScene::RectDrawEnd(const RECT & tileRc)
{
	
	int posx = rectDraw.left - tileRc.left, posy = rectDraw.top - tileRc.top;
	int LindexX = posx / tile_Size.cx;
	int LindexY = posy / tile_Size.cy;

	posx = rectDraw.right - tileRc.left;
	posy = rectDraw.bottom - tileRc.top;

	int RindexX = posx / tile_Size.cx;
	int RindexY = posy / tile_Size.cy;

	int index; 

	if (isCollisionLayer)
	{
		WorklistAdd();
		for (int i = LindexY; i <= RindexY; i++)
		{

			for (int j = LindexX; j <= RindexX; j++)
			{
				index = (i + tileCamePos.y) * tile_X + (j + tileCamePos.x);
				tiles[index].geometryinfo = geometryinfo;
				index = (index);
				tiles[index].geometryinfo = geometryinfo;
				if (tilesgeometry[index])
					tilesgeometry[index]->Release();
				D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&tilesgeometry[index]);
				GetGeomrtyPoint(tilesgeometry[index], tiles[index].geometryinfo, tiles[((i)* tile_X + (j))].rc);
			}
		}

	}
	else
	{
		WorklistAdd();
		for (int i = LindexY; i <= RindexY; i++)
		{
			for (int j = LindexX; j <= RindexX; j++)
			{
				tiles[(i + tileCamePos.y) * tile_X + (j + tileCamePos.x)].frameX = selectTile.frameX;
				tiles[(i + tileCamePos.y) * tile_X + (j + tileCamePos.x)].frameY = selectTile.frameY;
				tiles[(i + tileCamePos.y) * tile_X + (j + tileCamePos.x)].rotation = selectTile.rotation;
				tiles[(i + tileCamePos.y) * tile_X + (j + tileCamePos.x)].isReverse = selectTile.isReverse;
			}
		}

	}

	//tiles[indexY * tile_X + indexX].frameX = selectTile.frameX;
	//tiles[indexY * tile_X + indexX].frameY = selectTile.frameY;
}

void TileMapToolScene::SelectRectDrawShow(HDC hdc)
{

	// 언재가 만들어라 
	//int rNum = (rectDraw.right - rectDraw.left )% tile_Size.cx == 0 ? rectDraw.left / tile_Size.cx : rectDraw.left / tile_Size.cx + 1;
	//int bNum = (rectDraw.bottom - rectDraw.top) % tile_Size.cx == 0 ? rectDraw.left / tile_Size.cx : rectDraw.left / tile_Size.cx + 1;

	//RECT tilerc = { 0  , 0 , tile_X * tile_Size.cx , tile_Y * tile_Size.cy };
	//int posx = rectDraw.left - tilerc.left, posy = rectDraw.top - tilerc.top;
	//int LindexX = posx / tile_Size.cx;
	//int LindexY = posy / tile_Size.cy;

	//posx = rectDraw.right - tilerc.left;
	//posy = rectDraw.bottom - tilerc.top;

	//int RindexX = posx / tile_Size.cx;
	//int RindexY = posy / tile_Size.cy;

	//for (int i = LindexX; i <= RindexX; i++)
	//{
	//	for (int j = LindexY; j <= RindexY; j++)
	//	{
	//		tiles[j * tile_X + i].frameX = selectTile.frameX;
	//		tiles[j * tile_X + i].frameY = selectTile.frameY;
	//	}
	//}
	//
}

void TileMapToolScene::Erase(const RECT& tileRc)
{
	int posx = g_ptMouse.x - tileRc.left, posy = g_ptMouse.y - tileRc.top;
	int indexX = posx / tile_Size.cx;
	int indexY = posy / tile_Size.cy;
	int index = (indexY + tileCamePos.y) * tile_X + (indexX + tileCamePos.x);
	if (isCollisionLayer)
	{
		WorklistAdd();
		tiles[index].geometryinfo.ReSet();
		SAFE_RELEASE(tilesgeometry[index]);

	}
	else
	{
		WorklistAdd();
		tiles[index].frameX = defaultFrame;
		tiles[index].frameY = defaultFrame;
		tiles[index].rotation = 0.0f;
		tiles[index].rotation = false ;

	}
}

void TileMapToolScene::Dropper(const RECT& tileRc)
{
	selectTiles.clear();
	int posx = g_ptMouse.x - tileRc.left, posy = g_ptMouse.y - tileRc.top;
	int indexX = posx / tile_Size.cx;
	int indexY = posy / tile_Size.cy;
	int index = (indexY + tileCamePos.y) * tile_X + (indexX + tileCamePos.x);
	if (isCollisionLayer)
	{
		geometryinfo = tiles[index].geometryinfo;
	}
	else
	{
		selectTile.frameX = tiles[index].frameX;
		selectTile.frameY = tiles[index].frameY;
		selectTile.rotation = tiles[index].rotation;
		selectTile.isReverse = tiles[index].isReverse;
		selectSize.cx = 1;
		selectSize.cy = 1;
		selectTiles.push_back(selectTile);
	}

}

void TileMapToolScene::CleanAll()
{
	WorklistAdd();
	for (int i = 0; (UINT)i < tile_Y * tile_X; i++)
	{
		tiles[i].frameX = defaultFrame;
		tiles[i].frameY = defaultFrame;
		tiles[i].rotation = 0.0f;
		tiles[i].isReverse = false;
		tiles[i].geometryinfo.ReSet();

		SAFE_RELEASE(tilesgeometry[i]);
	}
	
}

void TileMapToolScene::SampleTileMoveSide(bool isLeft)
{
	if (isLeft)
	{
		//if (sampleTileDraw.startx > 0)
		if (moveFrame.x > 0)
		{
			moveFrame.x -= 1;
			sampleTileDraw.atlasInfo.costumAtlasSize.x -= 32.0f;
			sampleTileDraw.atlasInfo.costumAtlasSize.z -= 32.0f;
			//sampleTileDraw.startx -= 32;
			samlpeTileMovepos.x -= 32;
		}
	}
	else
	{
		//if ((LONG)tileDrawX + sampleTileDraw.startx < sampleTile->GetImageInfo()->width)
		if (tileDrawX + (moveFrame.x * tile_Size.cx) < sampleTile->GetSize().width)
		{
			moveFrame.x += 1;
			sampleTileDraw.atlasInfo.costumAtlasSize.x += 32.0f;
			sampleTileDraw.atlasInfo.costumAtlasSize.z += 32.0f;
			//sampleTileDraw.startx += 32;
			samlpeTileMovepos.x += 32;
		}
	}
}

void TileMapToolScene::SampleTileMoveUp(bool isUp)
{
	if (isUp)
	{
		//if (sampleTileDraw.starty > 0)
		if (moveFrame.y > 0)
		{
			moveFrame.y -= 1;
			sampleTileDraw.atlasInfo.costumAtlasSize.y -= 32.0f;
			sampleTileDraw.atlasInfo.costumAtlasSize.w -= 32.0f;
			//sampleTileDraw.starty -= 32;
			samlpeTileMovepos.y -= 32;
		}
	}
	else
	{
		//if ((LONG)tileDrawY + sampleTileDraw.starty < sampleTile->GetImageInfo()->height)
		if (tileDrawY + (moveFrame.y * tile_Size.cy) < sampleTile->GetSize().height)
		{
			moveFrame.y += 1;
			sampleTileDraw.atlasInfo.costumAtlasSize.y += 32.0f;
			sampleTileDraw.atlasInfo.costumAtlasSize.w += 32.0f;
			//sampleTileDraw.starty += 32;
			samlpeTileMovepos.y += 32;
		}
	}
}

void TileMapToolScene::TileMoveSide(bool isLeft)
{
	if (isLeft)
	{
		if (tileCamePos.x > 0)
		{
			tileCamePos.x--;
			ReDrawGeometry();
		}
	}
	else
	{
		if ((UINT)tileCamePos.x < (tile_X - tile_Render_X))
		{
			tileCamePos.x++;
			ReDrawGeometry();
		}
	}
}

void TileMapToolScene::TileMoveUp(bool isUp)
{
	if (isUp)
	{
		if (tileCamePos.y > 0)
		{
			tileCamePos.y--;
			ReDrawGeometry();
		}
	}
	else
	{
		if ((UINT)tileCamePos.y < (tile_Y - tile_Render_Y))
		{
			tileCamePos.y++;
			ReDrawGeometry();
		}
	}
}

void TileMapToolScene::SetGeometry(GeometryKinds kinds)
{
	switch (kinds)
	{
	case GeometryKinds::Triangle:
		geometryinfo.geometrykind = kinds;
		geometryinfo.width =	(float)tile_Size.cx;
		geometryinfo.height =	(float)tile_Size.cy;
		geometryinfo._width =	0.0f;
		geometryinfo._height =	0.0f;
		geometryinfo.rotation = 0.0f;
		break;
	case GeometryKinds::Square:
		geometryinfo.geometrykind = kinds;
		geometryinfo.width =	(float)tile_Size.cx;
		geometryinfo.height =	(float)tile_Size.cy;
		geometryinfo._width =	0.0f;
		geometryinfo._height =	0.0f;
		geometryinfo.rotation = 0.0f;
		break;
	case GeometryKinds::Trapezoid:
		geometryinfo.geometrykind = kinds;
		geometryinfo.width =   (float)tile_Size.cx ;
		geometryinfo.height =  (float)tile_Size.cy / 2;
		geometryinfo._width =  (float)tile_Size.cx ;
		geometryinfo._height = (float)tile_Size.cy / 2;
		geometryinfo.rotation = 0.0f;
		break;
	default:
		geometryinfo.geometrykind = GeometryKinds::None;
		geometryinfo.width =	0.0f;
		geometryinfo.height =	0.0f;
		geometryinfo._width =	0.0f;
		geometryinfo._height = 0.0f;
		geometryinfo.rotation = 0.0f;
		break;
	}
}

void TileMapToolScene::GetGeomrtyPoint(const GeometryInfo& geomrtyinfo)
{
	ID2D1GeometrySink* sink = NULL;

	Matrix3x2F matrix = Matrix3x2F::Rotation(geomrtyinfo.rotation, { (float)g_ptMouse.x, (float)g_ptMouse.y });

	if (geomrtyinfo.isRevers)
		matrix = matrix * Matrix3x2F::Scale({ -1.0f,1.0f }, { (float)g_ptMouse.x, (float)g_ptMouse.y });
	HRESULT s = geometry->Open(&sink);
	switch (geomrtyinfo.geometrykind)
	{
	case GeometryKinds::Triangle:
	{
		sink->BeginFigure(matrix.TransformPoint(D2D1::Point2F(g_ptMouse.x - geomrtyinfo.width / 2, g_ptMouse.y - geomrtyinfo.height / 2)), D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[2] = { {g_ptMouse.x - geomrtyinfo.width / 2,g_ptMouse.y + geomrtyinfo.height / 2},
									{g_ptMouse.x + geomrtyinfo.width / 2,g_ptMouse.y + geomrtyinfo.height / 2} };
		point[0] = matrix.TransformPoint(point[0]);
		point[1] = matrix.TransformPoint(point[1]);

		sink->AddLines(point, 2);
		// 피겨의 끝.
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		break;
	}
	case GeometryKinds::Square:
	{
		sink->BeginFigure(matrix.TransformPoint(D2D1::Point2F(g_ptMouse.x - geomrtyinfo.width / 2, g_ptMouse.y - geomrtyinfo.height / 2)), D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[3] = { {g_ptMouse.x - geomrtyinfo.width / 2,g_ptMouse.y + geomrtyinfo.height / 2},
									{g_ptMouse.x + geomrtyinfo.width / 2,g_ptMouse.y + geomrtyinfo.height / 2},
									{g_ptMouse.x + geomrtyinfo.width / 2,g_ptMouse.y - geomrtyinfo.height / 2} };

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
		
		//(g_ptMouse.x - geomrtyinfo.width / 2, g_ptMouse.y + (geomrtyinfo.height /2))
		sink->BeginFigure(matrix.TransformPoint(D2D1::Point2F(g_ptMouse.x - geomrtyinfo.width / 2, g_ptMouse.y - geomrtyinfo.height / 2)), D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[4] = { {g_ptMouse.x - geomrtyinfo.width / 2,g_ptMouse.y + geomrtyinfo.height / 2},
									{g_ptMouse.x + geomrtyinfo.width / 2,g_ptMouse.y + geomrtyinfo.height / 2},
									{g_ptMouse.x + geomrtyinfo.width / 2,g_ptMouse.y - geomrtyinfo.height / 2} ,
									{g_ptMouse.x - geomrtyinfo.width / 2,g_ptMouse.y - (geomrtyinfo.height / 2 + (geomrtyinfo._height))} };


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
	//sink->Release();
}

void TileMapToolScene::GetGeomrtyPoint(ID2D1PathGeometry* const geometry, const GeometryInfo & geomrtyinfo, RECT rect)
{
	ID2D1GeometrySink* sink = NULL;

	HRESULT s = geometry->Open(&sink);
	if (sink == nullptr)
		return;
	D2D1_POINT_2F start;
	Matrix3x2F matrix = Matrix3x2F::Rotation(geomrtyinfo.rotation, { (float)rect.left + ((float)rect.right - (float)(rect.left)) / 2,(float)rect.top + ((float)rect.right - (float)(rect.left)) / 2 });
	if (geomrtyinfo.isRevers)
		matrix = matrix * Matrix3x2F::Scale({ -1.0f,1.0f }, { (float)rect.left + ((float)rect.right - (float)rect.left) / 2.0f, (float)rect.bottom + ((float)rect.bottom - (float)rect.top) / 2.0f });
	switch (geomrtyinfo.geometrykind)
	{
	case GeometryKinds::Triangle:
	{
		start = D2D1::Point2F((float)rect.left, (float)rect.bottom);
		start = matrix.TransformPoint(start);
		sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[2] = { (float)rect.left + (float)geomrtyinfo.width ,(float)rect.bottom ,
											(float)rect.left  ,rect.bottom - (float)geomrtyinfo.height };
		point[0] = matrix.TransformPoint(point[0]);
		point[1] = matrix.TransformPoint(point[1]);
		sink->AddLines(point, 2);
		// 피겨의 끝.
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		break;
	}
	case GeometryKinds::Square:
	{
		start = matrix.TransformPoint({ (float)rect.left, (float)rect.bottom });
		sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[3] = {	{(float)rect.left + geomrtyinfo.width,(float)rect.bottom},
											{(float)rect.left + geomrtyinfo.width,(float)rect.bottom - geomrtyinfo.height},
											{(float)rect.left ,(float)rect.bottom - geomrtyinfo.height} };
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
		
		start = matrix.TransformPoint({ (float)rect.left, (float)rect.bottom });
		sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
		D2D1_POINT_2F point[4] = {	(float)rect.left, (float)rect.bottom - (geomrtyinfo.height + geomrtyinfo._height),
											{(float)rect.left + geomrtyinfo.width,(float)rect.bottom - geomrtyinfo.height},
											{(float)rect.left + geomrtyinfo.width,(float)rect.bottom},
											{(float)rect.left ,(float)rect.bottom}};
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

void TileMapToolScene::Save()
{

	char szFile[256];
	//API file dialog
	OPENFILENAMEA sfn;
	ZeroMemory(&sfn, sizeof(sfn));
	sfn.lStructSize = sizeof(sfn);
	sfn.hwndOwner = NULL;
	sfn.lpstrFile = szFile;
	sfn.lpstrFile[0] = '\0';
	sfn.nMaxFile = sizeof(szFile);
	sfn.lpstrFilter = "Map\0*.map\0";
	sfn.nFilterIndex = 1;
	sfn.lpstrFileTitle = NULL;
	sfn.nMaxFileTitle = 0;
	sfn.lpstrInitialDir = NULL;
	sfn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	BOOL ret = GetSaveFileNameA(&sfn);//GetOpenFileNameA(&ofn);
	if (ret) {
		// load map and enter training mode

		string saveFileName = sfn.lpstrFile;
		saveFileName = saveFileName + ".map";
		Save(saveFileName.c_str());
		isOpen = true;
	}

}

void TileMapToolScene::Save(const char * filename)
{
	// 몇바이트가 저장이됫는지
	DWORD writtenByte;
	HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int size[2] = { (int)tile_X,(int)tile_Y };
	WriteFile(hFile, size, 2 * sizeof(int), &writtenByte, NULL);
	DEBUG_MASSAGE("저장된 용량 %d byte", writtenByte);
	WriteFile(hFile, tiles, tile_X * tile_Y * sizeof(TILE), &writtenByte, NULL);
	DEBUG_MASSAGE("저장된 용량 %d byte\n", writtenByte);

	CloseHandle(hFile);
}

void TileMapToolScene::Load()
{
	char szFile[256];
	//API file dialog
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Map\0*.map\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	BOOL ret = GetOpenFileNameA(&ofn);
	if (ret) {
		WorklistAdd();
		//string loadFileName = ofn.lpstrFile;
		//loadFileName = loadFileName + ".map";
		// 몇바이트가 읽었는지
		DWORD readByte;
		HANDLE hFile = CreateFile(ofn.lpstrFile/*"Save/saveMapData.map"*/, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


		int size[2];
		ReadFile(hFile, size, 2 * sizeof(int), &readByte, NULL);
		delete[] tiles;
		tiles = nullptr;
		Resize((UINT)size[0], (UINT)size[1]);
		temptile_X = size[0];
		temptile_Y = size[1];
		ReadFile(hFile, tiles, size[0] * size[1] * sizeof(TILE), &readByte, NULL);
		isOpen = true;
		CloseHandle(hFile);
	}
}

void TileMapToolScene::LayerLoad()
{
	char szFile[256];
	//API file dialog
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Map\0*.map\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	BOOL ret = GetOpenFileNameA(&ofn);
	if (ret) {
		// 몇바이트가 읽었는지
		DWORD readByte;
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		// 레이어를 먼저 삭제해준다. 
		DeleteLayer();
		// 레이서 생성
		layerTile = new LayerTile;
		int size[2];
		ReadFile(hFile, size, 2 * sizeof(int), &readByte, NULL);
		layerTile->tile_X = size[0];
		layerTile->tile_Y = size[1];
		// 타일을 생성한다
		layerTile->tiles = new TILE[size[0] * size[1]];
		DWORD readSize = size[0] * size[1] * sizeof(TILE);
		ZeroMemory(layerTile->tiles, readSize);
		ReadFile(hFile, layerTile->tiles, readSize, &readByte, NULL);
		isOpen = true;
		CloseHandle(hFile);
	}

}

void TileMapToolScene::Resize(UINT width, UINT height)
{
	
	// 내가 25사이즈보다 작으면 안되서 넣어둔 조건
	UINT tempWidth = width > tile_Render_X ? width : tile_Render_X;
	UINT tempHeight = height > tile_Render_Y ? height : tile_Render_Y;
	int index = 0;
	// 타일이 존재하지 않을경우 할당
	if (tiles == nullptr)
	{
		tiles = new TILE[tempWidth*tempHeight];
		tilesgeometry = new ID2D1PathGeometry*[tempWidth*tempHeight];
		for (UINT i = 0; i < tempWidth*tempHeight; i++)
		{
			tilesgeometry[i] = nullptr;
		}
	}
	else
	{
		WorklistAdd();
		// 새로운 타일생성
		TILE* temp = new TILE[tempWidth*tempHeight];
		ID2D1PathGeometry** tempGeometry = new ID2D1PathGeometry*[tempWidth*tempHeight];
		for (int i = 0; (UINT)i < tempHeight; i++)
		{
			
			// Y 사이즈가 이전 타일보다 커지면 데이터 없음으로 반복문 종료
			if ((UINT)i >= tile_Y)
				break;
			for (int j = 0; (UINT)j < tempWidth; j++)
			{
				// X 사이즈가 이전 타일보다 커지면 데이터 없음으로 y축변경
				if ((UINT)j >= tile_X)
					break;
				// 이전 정보를 넣는다
				temp[(i * tempWidth) + j] = tiles[(i * tile_X) + j];
				tempGeometry[(i * tempWidth) + j] = tilesgeometry[(i * tile_X) + j];
			}
			// 축소 변환시 기하학정보 삭제
			if (tile_X > tempWidth)
			{
				for (UINT k = 0; k < tile_X - tempWidth; k++)
				{
					index = (i * tile_X) + tempWidth + k;
					if (index == ((i + 1) * tile_X))
						break;
					SAFE_RELEASE(tilesgeometry[(i * tile_X) + tempWidth + k]);
					
				}
			}
		}

		delete[] tilesgeometry;
		tilesgeometry = nullptr;
		tilesgeometry = tempGeometry;
		// 이전타일 할당해제
		delete[] tiles;
		tiles = nullptr;
		// 새로 만든 타일의 주소값을 현재 타일에다가 넘겨준다.
		tiles = temp;
	}
	// 현재 타일의 최대값들을 저장한다.
	tile_X = tempWidth;
	tile_Y = tempHeight;
	// 카메라위치 초기화 
	tileCamePos = { 0,0 };
}

void TileMapToolScene::NumberKeyInput(bool isSizex)
{
	KeyManager* keyManager = KEYMANAGER;

	for (int i = 0; i < 10; i++)
	{
		if (isSizex)
			OnceNumberKey(VK_NUMPAD0 + i, temptile_X);
		else
			OnceNumberKey(VK_NUMPAD0 + i, temptile_Y);
	}
	if (keyManager->IsOnceKeyDown(VK_BACK))
	{
		if (isSizex)
		{
			
			temptile_X /= 10;
			if (temptile_X < 0)
				temptile_X = 0;
			
		}
		else
		{
			temptile_Y /= 10;
			if (temptile_Y < 0)
				temptile_Y = 0;
		}
		numCount--;
	}
}

void TileMapToolScene::OnceNumberKey(int key, UINT& value)
{
	int tmep;
	if (KEYMANAGER->IsOnceKeyDown(key))
	{
		if (numCount < 3)
		{
			tmep = (int)(powf(10.0f, (float)numCount));
			value = ((10 * value) + (key - VK_NUMPAD0));
			numCount++;
		}
	}
}

void TileMapToolScene::QuickSave()
{
	if (!isOpen)
		Save("Save/QuickSave.map");	
	else
		Save("QuickSave.map");
}

void TileMapToolScene::AutoSave()
{
	DEBUG_MASSAGE("오토 세이브 \n");
	string autoSavestr;
	if (!isOpen)
		autoSavestr = "Save/AutoSave" + to_string(autoSaveCount) + ".map";
	else
		autoSavestr = "AutoSave" + to_string(autoSaveCount) + ".map";

	Save(autoSavestr.c_str());

	autoSaveCount++;
	if (autoSaveCount > maxAutoSave)
		autoSaveCount = 0;
}

void TileMapToolScene::ReDrawGeometry()
{
	for (UINT i = 0; i < tile_Render_X*tile_Render_Y; i++)
	{
		if (tilesgeometry[i])
		{
			tilesgeometry[i]->Release();
			tilesgeometry[i] = nullptr;
		}
	}
	int index;
	for (int i = 0; i < tile_Render_Y; i++)
	{
		for (int j = 0; j < tile_Render_X; j++)
		{
			index = (tile_X * (i + tileCamePos.y)) + (j + tileCamePos.x);
			if (tilesgeometry[index])
				tilesgeometry[index]->Release();
			D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&tilesgeometry[index]);
			GetGeomrtyPoint(tilesgeometry[index],tiles[index].geometryinfo, tiles[i * tile_X + j].rc);
		}
	}
}

void TileMapToolScene::GeometryInfoKeyInput()
{
	KeyManager* key = KEYMANAGER;
	if (isCollisionLayer)
	{
		if (key->IsOnceKeyDown(_1Key))
			SetGeometry(GeometryKinds::Triangle);
		if (key->IsOnceKeyDown(_2Key))
			SetGeometry(GeometryKinds::Square);
		if (key->IsOnceKeyDown(_3Key))
			SetGeometry(GeometryKinds::Trapezoid);

		float value = 0.0f;
		// 업
		if ((key->IsStayKeyDown(VK_SHIFT)))
		{
			value = 1.0f;
			// 세밀 조정
			if ((key->IsStayKeyDown(VK_CONTROL)))
			{
				value = 0.1f;
			}

		}
		// 다운
		else
		{
			value = -1.0f;
			// 세밀 조정
			if ((key->IsStayKeyDown(VK_CONTROL)))
			{
				value = -0.1f; 
			}
		}

		// 높이
		if (key->IsOnceKeyDown(ZKey))
		{
			geometryinfo.height += value;

			if (geometryinfo.height + geometryinfo._height >= ((float)tile_Size.cy ))
				geometryinfo.height -= value;
			else if (geometryinfo.height <= 0.0f)
				geometryinfo.height = 0.0f;
		}
		// 너비
		if (key->IsOnceKeyDown(XKey))
		{
			geometryinfo.width += value;
			if (geometryinfo.width >= (float)tile_Size.cy)
				geometryinfo.width = (float)tile_Size.cy;
			else if (geometryinfo.width <= 0.0f)
				geometryinfo.width = 0.0f;
		}
		// 사다리꼴 높이 
		if (key->IsOnceKeyDown(CKey))
		{
			geometryinfo._height += value;
			if (geometryinfo._height + geometryinfo.height >= ((float)tile_Size.cy ))
				geometryinfo._height -= value;
			else if (geometryinfo._height <= 0.0f)
				geometryinfo._height = 0.0f;
		}
		// 사다리꼴 너비
		if (key->IsOnceKeyDown(VKey))
		{
			geometryinfo._width += value;
			if (geometryinfo._width >= (float)tile_Size.cy)
				geometryinfo._width = (float)tile_Size.cy;
			else if (geometryinfo._width <= 0.0f)
				geometryinfo._width = 0.0f;
		}
	}
}

void TileMapToolScene::TileIndexMoveUP(bool isUP)
{
	if (selectTiles.size() == 1)
	{
		if (isUP)
		{
			if (selectTiles[0].frameY > 0)
				selectTiles[0].frameY--;
		}
		else
		{
			(selectTiles[0].frameY < sampleTile->GetSize().height / 32.0f);
				selectTiles[0].frameY++;
		}
	}
}

void TileMapToolScene::TileIndexMoveSide(bool isleft)
{
	if (selectTiles.size() == 1)
	{
		if (isleft)
		{
			if (selectTiles[0].frameX > 0)
				selectTiles[0].frameX--;
		}
		else
		{
			(selectTiles[0].frameX < sampleTile->GetSize().width / 32.0f);
			selectTiles[0].frameX++;
		}
	}
}

void TileMapToolScene::Undo()
{
	if (!worklist.empty())
	{
		Worklist* oldWorklist = worklist.back();
		worklist.pop_back();
		if ( (oldWorklist->tile_X != tile_X) |
			(oldWorklist->tile_Y != tile_Y))
		{
			Resize(oldWorklist->tile_X, oldWorklist->tile_Y);
			temptile_X = oldWorklist->tile_X;
			temptile_Y = oldWorklist->tile_Y;
		}
		memcpy_s(tiles, sizeof(TILE) *tile_X*tile_Y, oldWorklist->tiles, sizeof(TILE) *tile_X*tile_Y);
	}
}

void TileMapToolScene::WorklistAdd()
{
	Worklist* newWorklist = new Worklist;
	newWorklist->tiles = new TILE[tile_X*tile_Y];
	memcpy_s(newWorklist->tiles, sizeof(TILE) *tile_X*tile_Y, tiles, sizeof(TILE) *tile_X*tile_Y);
	newWorklist->tile_X = tile_X;
	newWorklist->tile_Y = tile_Y;
	worklist.push_back(newWorklist);
	if (maxWorklist < (UINT)worklist.size())
	{
		Worklist* oldWorklist = worklist.front();
		worklist.pop_front();
		SAFE_ARR_DELETE(oldWorklist->tiles);
		SAFE_DELETE(oldWorklist);
	}
}

void TileMapToolScene::DeleteLayer()
{
	if (layerTile)
	{
		SAFE_ARR_DELETE(layerTile->tiles);
		delete[] layerTile;
		layerTile = nullptr;
	}
}

