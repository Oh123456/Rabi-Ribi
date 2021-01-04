#include "AIBase.h"

AIBase::AIBase() : 
	owner(nullptr)
{
}

AIBase::~AIBase()
{
}

HRESULT AIBase::Init()
{
	return S_OK;
}

void AIBase::Release()
{
	Super::Release();
}

void AIBase::Update()
{
	Super::Update();
}

void AIBase::Render()
{
	Super::Render();
}
