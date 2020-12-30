#pragma once
#include "pch.h"
#include "Singleton.h"

class Camera : public Singleton<Camera>
{
public:
	Camera();
	~Camera();

	HRESULT Init();
	void Update();

	inline void SetLocation(const Location& location)					{ this->location = location; }
	inline void MoveCamera(const Location& location)				{ this->location.x += location.x, this->location.y += location.y; }
	inline void MoveCamera(float x, float y = 0.0f)						{ this->location.x += x, this->location.y += y; }
	inline void SetMapMaxLocation(const Location& location)		{ this->mapMaxLocation = location; }

	void SetFocusActor(class Actor* actor)								{ this->focusActor = actor;}
	void SetZoom(const Scale& scale);


	inline const Location& GetLocation() const							{ return location; }
	inline const Scale& GetZoom() const								{ return zoomScale; }
	inline const class Actor* GetFocusActor() const					{ return focusActor;}
private:
	Location location;
	Location mapMaxLocation;
	Scale zoomScale;
	class Actor* focusActor;
};

