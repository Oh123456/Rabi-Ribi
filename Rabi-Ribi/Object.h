#pragma once
#include "ObjectBase.h"

// 모든 클래스의 기본
class Object : public ObjectBase
{
	typedef multimap<ZOrder, Object*, greater<ZOrder>> Render_mapList;
	typedef Render_mapList::const_iterator ObjectmultiMap_Const_Iterator;
	typedef Render_mapList::iterator ObjectmultiMap_Iterator;


	typedef list<Object*> ObjectList;
	typedef ObjectList::const_iterator ObjectList_Const_Iterator;
	typedef ObjectList::iterator ObjectList_Iterator;

public:
	Object() : isValid(true), isRender(true), isNotUPdate(false),zOrder(10), parentsObject(nullptr) {};
	virtual ~Object() {};

	//  멤버 변수 초기화, 메모리 할당
	virtual HRESULT Init();
	// 메모리 해제
	virtual void Release();
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	virtual void Update();
	// 프레임 단위 출력 (이미지, 텍스트)
	virtual void Render();

	// 오브젝트 생성
	template<class T>
	inline T* CreateObject(bool isRender = true)
	{
		Object* newObject = new T();
		newObject->SetParentsObject(this);
		newObject->Init();
		if (isRender)
			object.insert(pair<ZOrder, Object*>(newObject->GetZOrder(), newObject));
		Object* pObject = const_cast<Object*>(newObject->GetParentsObject());
		newObject->UPdateListAdd(pObject->GetUpdateChilds());
		allClass.push_back(newObject);
		return Cast<T>(newObject);
	}
	// 씬(맵, 레벨) 생성
	template<class T>
	inline T* CreateScene(bool isValid = false)
	{
		Object* newObject = new T();
		newObject->SetParentsObject(this);
		newObject->SetIsValid(isValid);
		allClass.push_back(newObject);
		return Cast<T>(newObject);
	}
	inline void UPdateListAdd(list<Object*>* object_UPdateList)
	{
		if (!isNotUPdate)
			object_UPdateList->push_back(this);
	}
	bool GetisActivation() { return this->isActivation; }
	// z 버퍼 설정
	void SetZOrder(ZOrder z);
	ZOrder GetZOrder() { return zOrder; }
	// 자식들의 렌더 오브젝트 얻어 오기
	multimap<ZOrder, Object*, greater<ZOrder>>* GetRenderChilds() { return &object; };
	// 자식들의 업데이트 오브젝트 얻어 오기
	list<Object*>* GetUpdateChilds() { return &object_UPdateList; }
	// 모든 자식들 얻어 오기
	list<Object*>* GetChilds() { return &allClass; }

	// 활성화 여부
	virtual void SetIsValid(bool value);
	inline bool GetIsValid() { return isValid; }

	void DeleteChild(Object* child);
	void SetIsRender(bool value);

	const Object* GetParentsObject() { return parentsObject; }
private:
	void SetParentsObject(Object* object) { parentsObject = object; }
protected:
	// 모든 자식 클래스
	list<Object*> allClass;
	// 자식의 업데이트 리스트
	list<Object*> object_UPdateList;
	// 자식의 렌더 오브젝트 리스트
	multimap<ZOrder, Object*, greater<ZOrder>>object;
	// 부모 객체
	Object* parentsObject;
	// 활성화
	bool isValid;
	// 업데이트 에서 제외
	bool isNotUPdate;
	//렌더링할지 말지
	bool isRender;
	//
	bool isActivation;
private:
	// z값
	ZOrder zOrder;
};

