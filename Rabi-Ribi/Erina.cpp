#include "Erina.h"
#include "D2DGraphic.h"


Erina::Erina()
{
}

Erina::~Erina()
{
}

HRESULT Erina::Init()
{
	location = { 350.0f,200.0f };                           
	size = { 20.0f,32.0f };
	imageInfo.imageName = L"Erina";
	imageInfo.imageLocation = location;
	imageInfo.atlasInfo.frameSize = { 64.0f,64.0f };
	imageInfo.atlasInfo.frame = {0,0};
	imageInfo.imageEffect = D2DIE_ATLAS;

	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&collisionGeomtry);
	ID2D1GeometrySink* sink = NULL;
	collisionGeomtry->Open(&sink);

	sink->BeginFigure({0,size.height}, D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F point[3] = {	{size.width,size.height},
								{size.width,0.0f},
								{0.0f,0.0f}};
	sink->AddLines(point,3);
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	sink->Release();
	//collisionGeomtry;

	return S_OK;
}

void Erina::Release()
{
}

void Erina::Update()
{
	location.y += 0.98f;
	imageInfo.imageLocation = location;
	if (KEYMANAGER->IsStayKeyDown(VK_UP))
		location.y -= 1.5f;
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
		location.y += 1.5f;
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
		location.x -= 1.5f;
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
		location.x += 1.5f;
}

void Erina::Render()
{
	Super::Render();
	IMAGEMANAGER->ImageRander(imageInfo);
}
