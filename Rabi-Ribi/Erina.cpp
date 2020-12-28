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


	moveSpeed = 1.0f;
	return S_OK;
}

void Erina::Release()
{
}

void Erina::Update()
{
	
	geomtryLocation = location;
	if (isFalling)
	{
		acceleration = 0.98f ;
		geomtryLocation.y += acceleration;
	}
	else
		acceleration = 0.0f;
	imageInfo.imageLocation = location;

	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		isFalling = true;
		location.y -= 12.8f;
		geomtryLocation.y -= 12.8f;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
		geomtryLocation.y += moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
		geomtryLocation.x -= moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
		geomtryLocation.x += moveSpeed * (TIMERMANAGER->GettimeElapsed() * 100.0f);



}

void Erina::Render()
{
	Super::Render();
	IMAGEMANAGER->ImageRander(imageInfo);
}
