#include "Hammer.h"
#include "HammerAnimInstance.h"
#include "D2DGraphic.h"
#include "GeometryCollision.h"
#include "Character.h"

Hammer::Hammer() : 
	animKinds(HammerAnimationKinds::None), attackKinds(AttackKinds::OneHit)
{
	animmation = CreateObject<HammerAnimInstance>();
	animmation->SetOwner(this);

	onHit.BindObject(this,&Hammer::OnHit);
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
	size = { 64.0f  ,64.0f };
	worldLocation = { 0.0f,0.0f };
	SetGeomtryCollsion();
	hitobjects.clear();

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
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ geomtryLocation.x - size.width / 2, geomtryLocation.y - size.height / 2 ,
																				 geomtryLocation.x + size.width / 2, geomtryLocation.y + size.height / 2 } ,brush);
	brush->SetColor(D2D1::ColorF(0x0000ff, 1.0f));
#endif // _DEBUG

}

void Hammer::OnHit(Object* object)
{
	Character* hitObject = Cast<Character>(object);
	if (attackKinds == AttackKinds::OneHit)
	{
		bool isNoHit = true;
		if ((object != owner) & (object != this) & (hitObject != nullptr))
		{
			size_t size = hitobjects.size();
			for (size_t i = 0; i < size; i++)
			{
				if (hitobjects[i] == hitObject)
				{
					isNoHit = false;
					break;
				}
			}
			if (isNoHit)
			{
				hitObject->TakeDamage(Cast<Character>(owner)->GetDamage());
				hitobjects.push_back(hitObject);
			}
		}
	}
	else
	{
		hitObject->SetInvincible(false);
		hitObject->TakeDamage(Cast<Character>(owner)->GetDamage());
	}
}