#include "GameNode.h"

GameNode::GameNode() :
	isValid(true),
	zOrder(10),
	parentsObject(nullptr),
	isNotUPdate(false),
	isActivation(true)
{
}

GameNode::~GameNode()
{
	this->Release();
}

HRESULT GameNode::Init()
{
	return S_OK;
}

void GameNode::Release()
{
	GameNodeListiterator it;
	//multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator it;
	GameNode* object;
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

void GameNode::Update()
{
	GameNodeListConst_iterator it;
	GameNodeList copyUpdatelist = this->object_UPdateList;
	//multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator it;
	GameNode* object = nullptr;
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

void GameNode::Render(HDC hdc)
{
	if (!this->isValid)
		return;
	//GameNodeListiterator it;
	multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator it;
	multimap<ZOrder, GameNode*, greater<ZOrder>> CopyRneder = object;
	GameNode* object;
	for (it = CopyRneder.begin(); it != CopyRneder.end(); it++)
	{
		object = it->second;
		if (object)
		{
			if (object->GetIsValid())
				object->Render(hdc);
			
		}
	}
}

void GameNode::SetZOrder(ZOrder z)
{
	if (this->parentsObject == nullptr)
		return;
	multimap<ZOrder, GameNode*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
	multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator it;
	it = childs->lower_bound(this->zOrder);

	GameNode* fineObject;
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

void GameNode::SetIsValid(bool value)
{
	if (this->parentsObject == nullptr)
		return;

	if (!value && this->isValid)
	{
		multimap<ZOrder, GameNode*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		GameNodeList* childsUpdateList = this->parentsObject->GetUpdateChilds();
		GameNodeListiterator uit;
		multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator it;
		it = childs->lower_bound(this->zOrder);
		this->isValid = value;
		//GameNode* fineObject;

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
		multimap<ZOrder, GameNode*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		GameNodeList* childsUpdateList = this->parentsObject->GetUpdateChilds();

		if (!this->isNotUPdate)
			childsUpdateList->push_back(this);
		childs->insert(pair<ZOrder, GameNode*>(zOrder, this));
		isActivation = true;
		
	}
}

void GameNode::SetIsRender(bool value)
{
	if (value & !this->isRender)
	{
		multimap<ZOrder, GameNode*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		multimap<ZOrder, GameNode*, greater<ZOrder>>::const_iterator it;
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
		multimap<ZOrder, GameNode*, greater<ZOrder>>* childs = this->parentsObject->GetRenderChilds();
		childs->insert(pair<ZOrder, GameNode*>(zOrder, this));
	}
}
