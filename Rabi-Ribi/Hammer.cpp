#include "Hammer.h"
#include "HammerAnimInstance.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"

Hammer::Hammer() : animKinds(HammerAnimationKinds::None)
{
	animmation = CreateObject<HammerAnimInstance>();
	animmation->SetOwner(this);
}

Hammer::~Hammer()
{
}

HRESULT Hammer::Init()
{
	IMAGEMANAGER->LoadPng(L"picoHammer",L"Weapon/hammer_a");
	imageInfo.imageName = L"picoHammer";
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.atlasInfo.frameSize = { 64.0,64.0f };
	size = { 64.0f * 1.2f ,64.0f };

	ID2D1PathGeometry* collsion;
	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&collsion);
	ID2D1GeometrySink* sink = NULL;
	collsion->Open(&sink);

	sink->BeginFigure({ 0,size.height }, D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F point[3] = { {size.width,size.height},
								{size.width,0.0f},
								{0.0f,0.0f} };
	sink->AddLines(point, 3);
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	sink->Release();


	collisionGeomtry = new GeometryCollision;

	collisionGeomtry->SetCollision(collsion, this);
	geomtryLocation = location;


	return S_OK;
}

void Hammer::Release()
{
	Super::Release();
}

void Hammer::Update()
{
	Super::Update();
	if (owner)
	{
		imageInfo.affineMatrix = owner->GetImageInfo_ptr()->affineMatrix;
		geomtryLocation = location;
		//location = owner->GetLocation();
		//imageInfo.imageLocation = location;
	}
}

void Hammer::Render()
{
	Super::Render();
#ifdef _DEBUG
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xf0f00f, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																				 location.x + size.width / 2, location.y + size.height / 2 },brush);
	brush->SetColor(D2D1::ColorF(0x0000ff, 1.0f));
#endif // _DEBUG

}
