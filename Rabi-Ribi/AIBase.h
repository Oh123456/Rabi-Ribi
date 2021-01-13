#pragma once
#include "Object.h"
class AIBase : public Object
{
	SUPER(Object);
public:
	AIBase();
	~AIBase();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	inline void SetOwner(const Object* owner) { this->owner = Cast<Object>(owner); }

protected:
	Object* owner;
};

