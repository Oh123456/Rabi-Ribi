#pragma once
#include "ObjectBase.h"

// ��� Ŭ������ �⺻
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

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual HRESULT Init();
	// �޸� ����
	virtual void Release();
	// ������ ���� ���� ���� ���� ( ������ ����)
	virtual void Update();
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	virtual void Render();

	// ������Ʈ ����
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
	// ��(��, ����) ����
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
	// z ���� ����
	void SetZOrder(ZOrder z);
	ZOrder GetZOrder() { return zOrder; }
	// �ڽĵ��� ���� ������Ʈ ��� ����
	multimap<ZOrder, Object*, greater<ZOrder>>* GetRenderChilds() { return &object; };
	// �ڽĵ��� ������Ʈ ������Ʈ ��� ����
	list<Object*>* GetUpdateChilds() { return &object_UPdateList; }
	// ��� �ڽĵ� ��� ����
	list<Object*>* GetChilds() { return &allClass; }

	// Ȱ��ȭ ����
	virtual void SetIsValid(bool value);
	inline bool GetIsValid() { return isValid; }

	void DeleteChild(Object* child);
	void SetIsRender(bool value);

	const Object* GetParentsObject() { return parentsObject; }
private:
	void SetParentsObject(Object* object) { parentsObject = object; }
protected:
	// ��� �ڽ� Ŭ����
	list<Object*> allClass;
	// �ڽ��� ������Ʈ ����Ʈ
	list<Object*> object_UPdateList;
	// �ڽ��� ���� ������Ʈ ����Ʈ
	multimap<ZOrder, Object*, greater<ZOrder>>object;
	// �θ� ��ü
	Object* parentsObject;
	// Ȱ��ȭ
	bool isValid;
	// ������Ʈ ���� ����
	bool isNotUPdate;
	//���������� ����
	bool isRender;
	//
	bool isActivation;
private:
	// z��
	ZOrder zOrder;
};

