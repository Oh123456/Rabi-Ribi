#include "PlayerInput.h"
#include "Erina.h"

PlayerInput::PlayerInput()
{
}

PlayerInput::~PlayerInput()
{
}

HRESULT PlayerInput::Init()
{
	bindingkey.clear();
	return S_OK;
}

void PlayerInput::Release()
{
	map<BindKeyInfo, OnKeyInput*>::const_iterator c_it;
	for (c_it = bindingkey.begin(); c_it != bindingkey.end(); c_it++)
	{
		c_it->second->UnBind();
		delete c_it->second;
	}
	bindingkey.clear();
}

void PlayerInput::Update()
{
	InputKey();
}

void PlayerInput::Render()
{
}

void PlayerInput::InputKey()
{
	KeyManager* keyManager = KEYMANAGER;
	multimap<BindKeyInfo, OnKeyInput*>::const_iterator c_it;
	BindKeyInfo bindkeyInfo;
	for (c_it = bindingkey.begin(); c_it != bindingkey.end(); c_it++)
	{
		bindkeyInfo = c_it->first;
		switch (bindkeyInfo.inputKinds)
		{
		case KeyInputKinds::Key_UP:
			if (keyManager->IsOnceKeyUP(bindkeyInfo.VK_key))
				c_it->second->Execute();
			break;
		case KeyInputKinds::Key_Down:
			if (keyManager->IsOnceKeyDown(bindkeyInfo.VK_key))
				c_it->second->Execute();
			break;
		case KeyInputKinds::StayKey_Down:
			if (keyManager->IsStayKeyDown(bindkeyInfo.VK_key))
				c_it->second->Execute();
			break;
		}
	}
}
