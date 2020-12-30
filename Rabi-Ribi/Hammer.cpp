#include "Hammer.h"
#include "Animinstance.h"

Hammer::Hammer()
{
	animmation = CreateObject<Animinstance>();
	animmation->SetOwner(this);
}

Hammer::~Hammer()
{
}

HRESULT Hammer::Init()
{
	IMAGEMANAGER->LoadPng(L"picoHammer",L"Weapon/hammer_a");
	imageInfo.imageName = L"picoHammer";
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_ATLAS;
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.atlasInfo.frameSize = { 64.0,64.0f };
	return S_OK;
}

void Hammer::Release()
{
	Super::Release();
}

void Hammer::Update()
{
	Super::Update();
}

void Hammer::Render()
{
	Super::Render();
}
