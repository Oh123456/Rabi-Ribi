#include "Wizard.h"
#include "ImageManager.h"
#include "WizardAnimInstance.h"
#include "D2DGraphic.h"

Wizard::Wizard() :
	wizardType(WizardType::Blue)
{
	animmation = CreateObject<WizardAnimInstance>();
	animmation->SetOwner(this);

}

Wizard::~Wizard()
{
}

HRESULT Wizard::Init()
{
	Super::Init();

	location = { 500.0f,0.0f };
	IMAGEMANAGER->LoadPng(L"oldboss3_a", L"Chacter/Enemy/oldboss3_a");
	imageInfo.imageName = L"oldboss3_a";
	imageInfo.atlasInfo.frameSize = { 48.0f,48.0f};
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, {24.0f,24.0f});
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	imageInfo.imageLocation = location;
	size = { 20.0f,50.0f };
	SetGeomtryCollsion();

	return S_OK;
}

void Wizard::Release()
{
	Super::Release();
}

void Wizard::Update()
{
	Super::Update();
	noAnimChange = false;
}

void Wizard::Render()
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

void Wizard::MoveCharacter(Vector2_F speed)
{
}
