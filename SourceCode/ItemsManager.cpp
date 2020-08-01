#include "ItemsManager.h"


ItemsManager * ItemsManager::_instance = NULL;

ItemsManager * ItemsManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new ItemsManager();
	}
	return _instance;
}

ItemsManager::ItemsManager()
{

}

void ItemsManager::AddItem(Items * Item)
{
	listItems.push_back(Item);
}

void ItemsManager::Update(DWORD dt, vector<LPGAMEOBJECT> *listObj)
{
	for (auto x : listItems)
	{
		if (!x->GetIsFinished())
		{
			x->Update(dt, listObj);
		}
	}

}

void ItemsManager::GetListItem(vector<LPGAMEOBJECT>& listItem, vector<LPGAMEOBJECT>* listObj)
{
	
}

ItemsManager::~ItemsManager()
{

}