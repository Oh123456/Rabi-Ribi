#include "Rabbit.h"
#include "RabbitAnimInstance.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"

Rabbit::Rabbit()
{
	animmation = CreateObject<RabbitAnimInstance>();
	animmation->SetOwner(this);

	moveSpeed = 100.0f;
}

Rabbit::~Rabbit()
{
}

HRESULT Rabbit::Init()
{
	Super::Init();
	IMAGEMANAGER->LoadPng(L"enemy1",L"Chacter/Enemy/enemy1_a");
	location = { 350.0f,100.0f };
	worldLocation = location;
	size = { 20.0f,20.0f };
	imageInfo.imageName = L"enemy1";
	imageInfo.imageLocation = { location.x ,location.y - 20.0f };
	imageInfo.atlasInfo.frameSize = { 48.0f,48.0f };
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.0f,1.0f }, { 48.0f,48.0f });
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;

	SetGeomtryCollsion();

	return S_OK;
}

void Rabbit::Release()
{
	Super::Release();
}

void Rabbit::Update()
{
	Super::Update();
	imageInfo.imageLocation = { location.x ,location.y - 10.0f };
	geomtryLocation.x += 0.11f;
	imageInfo.affineMatrix = Matrix3x2F::Scale({ -1.0f,1.0f }, { 24.0f,24.0f });
}

void Rabbit::Render()
{
	Super::Render();
#ifdef _DEBUG
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xf0f00f, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																				 location.x + size.width / 2, location.y + size.height / 2 }, brush);
	brush->SetColor(D2D1::ColorF(0x0000ff, 1.0f));
#endif // _DEBUG
}
