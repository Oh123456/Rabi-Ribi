#pragma once
#include "Object.h"


DELEGATE(OnKeyInput);

enum class KeyInputKinds
{
	Key_UP,
	Key_Down,
	StayKey_Down
};

class PlayerInput : public Object
{
	SUPER(Object);
	template<typename UserClass>
	struct Memptr
	{
		typedef typename void(UserClass::* Type)();
	};

	struct BindKeyInfo
	{
		BindKeyInfo() :
			VK_key(0) , inputKinds(KeyInputKinds::Key_UP)
		{
		}

		BindKeyInfo(UINT VK_value, KeyInputKinds inputKinds) :
			VK_key(VK_value), inputKinds(inputKinds)
		{
		}

		bool operator < (const BindKeyInfo& sru) const
		{
			if (this->VK_key < sru.VK_key)
				return true;
			return false;
		}

		UINT VK_key;
		KeyInputKinds inputKinds;

	};
public:
	PlayerInput();
	~PlayerInput();

	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init() override;
	// 메모리 해제
	void Release() override;
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update() override;
	// 프레임 단위 출력 (이미지, 텍스트)
	void Render() override;


	template <typename UserClass>
	void BindInputKey(UINT VK_value, KeyInputKinds inputKinds, UserClass* userClass, typename Memptr<UserClass>::Type memfun)
	{
		BindKeyInfo newKeyinfo(VK_value, inputKinds);
		map<BindKeyInfo, OnKeyInput*>::const_iterator c_it = bindingkey.find(newKeyinfo);
		OnKeyInput* Key = nullptr;
		if (c_it == bindingkey.end())
		{
			Key = new OnKeyInput();
			Key->BindObject(userClass, memfun);
			bindingkey.insert(make_pair(newKeyinfo,Key));
		}
		else
		{
			Key = c_it->second;
			Key->UnBind();
			Key->BindObject(userClass, memfun);
		}
	}
private:
	void InputKey();
private:
	map<BindKeyInfo, OnKeyInput*> bindingkey;
};

