#pragma once
#include"Items.h"
#include "GameObject.h"
#include "AppleItem.h"
#include "CGame.h"

class ItemsManager
{
	static ItemsManager *_instance;
	vector<Items*> listItems;
public:
	ItemsManager();
	~ItemsManager();
	void AddItem(Items * Item);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObj);
	void Render();
	void GetListItem(vector<LPGAMEOBJECT> &listItem, vector<LPGAMEOBJECT> *listObj);
	static ItemsManager *GetInstance();

};
