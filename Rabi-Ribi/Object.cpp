#include "Object.h"

HRESULT Object::Init()
{
	return S_OK;
}

void Object::Release()
{
	ObjectList_Iterator it;
	//multimap<ZOrder, Object*, greater<ZOrder>>::const_iterator it;
	Object* object;
	for (it = this->allClass.begin(); it != this->allClass.end(); it++)
	{
		object = *it;// ->second;
		if (object != nullptr)
		{
			object->Release();
			delete object;
			object = nullptr;
		}
	}
	this->object.clear();
	this->object_UPdateList.clear();
	this->allClass.clear();
}

void Object::Update()
{
	ObjectList_Const_Iterator it;
	ObjectList copyUpdatelist = this->object_UPdateList;
	//multimap<ZOrder, Object*, greater<ZOrder>>::const_iterator it;
	Object* object = nullptr;
	for (it = copyUpdatelist.begin(); it != copyUpdatelist.end();)
	{
		object = *it;
		it++;
		if (object)
		{
			object->Update();
		}
	}

}

void Object::Render()
{
	if (!this->isValid)
		return;
	//ObjectListiterator it;
	multimap<ZOrder, Object*, greater<ZOrder>>::const_iterator it;
	multimap<ZOrder, Object*, greater<ZOrder>> CopyRneder = object;
	Object* object;
	for (it = CopyRneder.begin(); it != CopyRneder.end(); it++)
	{
		object = it->second;
		if (object)
		{
			if (object->GetIsValid())
				object->Render();

		}
	}
}

void Object::SetZOrder(ZOrder z)
{
	if (this->parentsObject == nullptr)
		return;
	multimap<ZOrder, Object*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
	multimap<ZOrder, Object*, greater<ZOrder>>::const_iterator it;
	it = childs->lower_bound(this->zOrder);

	Object* fineObject;
	for (; it != childs->upper_bound(this->zOrder); it++)
	{
		if (it->second == this)
		{
			fineObject = it->second;
			childs->erase(it);
			this->zOrder = z;
			childs->insert(make_pair(zOrder, fineObject));
			break;
		}
	}
}

void Object::SetIsValid(bool value)
{
	if (this->parentsObject == nullptr)
		return;

	if (!value && this->isValid)
	{
		multimap<ZOrder, Object*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		ObjectList* childsUpdateList = this->parentsObject->GetUpdateChilds();
		ObjectList_Iterator uit;
		multimap<ZOrder, Object*, greater<ZOrder>>::const_iterator it;
		it = childs->lower_bound(this->zOrder);
		this->isValid = value;
		//Object* fineObject;

		for (; it != childs->upper_bound(this->zOrder); it++)
		{
			if (it->second == this)
			{
				childs->erase(it);
				break;
			}
		}

		for (uit = childsUpdateList->begin(); uit != childsUpdateList->end(); uit++)
		{
			if (*uit == this)
			{
				childsUpdateList->erase(uit);
				break;
			}
		}
		isActivation = false;
	}
	else if (value && !this->isValid)
	{
		this->isValid = value;
		multimap<ZOrder, Object*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		ObjectList* childsUpdateList = this->parentsObject->GetUpdateChilds();

		if (!this->isNotUPdate)
			childsUpdateList->push_back(this);
		childs->insert(pair<ZOrder, Object*>(zOrder, this));
		isActivation = true;

	}
}

void Object::SetIsRender(bool value)
{
	if (value & !this->isRender)
	{
		multimap<ZOrder, Object*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		multimap<ZOrder, Object*, greater<ZOrder>>::const_iterator it;
		it = childs->lower_bound(this->zOrder);
		this->isRender = value;

		for (; it != childs->upper_bound(this->zOrder); it++)
		{
			if (it->second == this)
			{
				childs->erase(it);
				break;
			}
		}
	}
	else if (!value & this->isRender)
	{
		this->isRender = value;
		multimap<ZOrder, Object*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		childs->insert(pair<ZOrder, Object*>(zOrder, this));
	}
}
