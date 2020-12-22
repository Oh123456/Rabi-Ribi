#pragma once
#include "pch.h"

/*
	앞으로 만들어질 게임의 가장 기본적인 구조가 되는 클래스

*/
class GameNode
{
protected:
	typedef list<GameNode*> GameNodeList;
	typedef list<GameNode*>::iterator GameNodeListiterator;
	typedef list<GameNode*>::const_iterator GameNodeListConst_iterator;

	typedef multimap<ZOrder, GameNode*, greater<ZOrder>> GameNodeRenderMap;
	typedef multimap<ZOrder, GameNode*, greater<ZOrder>>::iterator GameNodeRenderMapiterator;
	typedef multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator GameNodeRenderMapConst_iterator;
public:
	GameNode();
	virtual ~GameNode();

	//  멤버 변수 초기화, 메모리 할당
	virtual HRESULT Init();
	// 메모리 해제
	virtual void Release();
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	virtual void Update();
	// 프레임 단위 출력 (이미지, 텍스트)
	virtual void Render(HDC hdc);

	// 오브젝트 생성
	template<class T>
	inline T* CreateObject(bool isRender = true)
	{
		GameNode* newObject = new T();
		newObject->SetParentsObject(this);
		newObject->Init();
		if (isRender)
			object.insert(pair<ZOrder,GameNode*>(newObject->GetZOrder(), newObject));
		GameNode* pObject = const_cast<GameNode*>(newObject->GetParentsObject());
		newObject->UPdateListAdd(pObject->GetUpdateChilds());
		allClass.push_back(newObject);
		return Cast<T>(newObject);
	}
	// 씬(맵, 레벨) 생성
	template<class T>
	inline T* CreateScene(bool isValid = false)
	{
		GameNode* newObject = new T();
		newObject->SetParentsObject(this);
		newObject->SetIsValid(isValid);
		allClass.push_back(newObject);
		return Cast<T>(newObject);
	}
	inline void UPdateListAdd(list<GameNode*>* object_UPdateList) 
	{
		if (!isNotUPdate) 
			object_UPdateList->push_back(this);
	}
	bool GetisActivation() { return this->isActivation; }
	// z 버퍼 설정
	void SetZOrder(ZOrder z);
	ZOrder GetZOrder() { return zOrder; }
	// 자식들의 렌더 오브젝트 얻어 오기
	multimap<ZOrder, GameNode*, greater<ZOrder>>* GetRenderChilds() { return &object; };
	// 자식들의 업데이트 오브젝트 얻어 오기
	list<GameNode*>* GetUpdateChilds() { return &object_UPdateList; }
	// 모든 자식들 업어 오기
	list<GameNode*>* GetChilds() { return &allClass; }

	void SetIsValid(bool value);
	inline bool GetIsValid()					{ return isValid; }

	void SetIsRender(bool value);

	const GameNode* GetParentsObject() { return parentsObject; }
private:
	void SetParentsObject(GameNode* object) { parentsObject = object; }
protected:
	// 모든 자식 클래스
	list<GameNode*> allClass;
	// 자식의 업데이트 리스트
	list<GameNode*> object_UPdateList;
	// 자식의 렌더 오브젝트 리스트
	multimap<ZOrder, GameNode*, greater<ZOrder>>object;
	// 부모 객체
	GameNode* parentsObject;
	// z값
	ZOrder zOrder;
	// 활성화
	bool isValid;
	// 업데이트 에서 제외
	bool isNotUPdate;
	//렌더링할지 말지
	bool isRender;
	//
	bool isActivation;
};

