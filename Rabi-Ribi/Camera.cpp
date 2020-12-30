#include "Camera.h"
#include "D2DGraphic.h"
#include "Character.h"

Camera::Camera() :
	location({ 0.0f,0.0f }), zoomScale({ 1.0f,1.0f }), mapMaxLocation({ 0.0f,0.0f }), focusActor(nullptr)
{
}

Camera::~Camera()
{
}

HRESULT Camera::Init()
{
	location = { 0,0 };
	zoomScale = { 1.0f,1.0f };
	focusActor = nullptr;
	return S_OK;
}

void Camera::Update()
{
	if (focusActor)
	{
		const Location& focusActorLocation = focusActor->GetLocation();
		float moveSpeed = Cast<Character>(focusActor)->GetMoveSpeed() / 60.0f;
		if ((focusActorLocation.x > 320.f) & (location.x < mapMaxLocation.x))
		{
			location.x += focusActorLocation.x - 320.f;
			//location.x += moveSpeed;
			if (location.x >= mapMaxLocation.x)
				location.x = mapMaxLocation.x;
			focusActor->SetGeomtryLocation({ 320.0f,focusActorLocation.y});
		}
		else if ((focusActorLocation.x < 320.f) & (location.x > 0.0f))
		{
			location.x += focusActorLocation.x - 320.f;
			if (location.x <= 0.0f)
				location.x = 0.0f;
			focusActor->SetGeomtryLocation({ 320.0f,focusActorLocation.y });
		}

	}
}

void Camera::SetZoom(const Scale& scale)
{
	D2D* d2d = GETMANAGER(D2D);
	ID2D1HwndRenderTarget* renderTarget = d2d->GetD2DRenderTarget();
	//renderTarget->SetTransform(Matrix3x2F::Scale({ 1.0f,1.0f }, {0.0f,0.0f}));

	renderTarget->SetTransform(Matrix3x2F::Scale({ scale.x , scale.y }, { 0.0f,0.0f }));
	zoomScale = scale;
}
