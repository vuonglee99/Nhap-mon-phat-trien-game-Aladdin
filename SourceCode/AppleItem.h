#pragma once
#include "GameObject.h"
#include "Items.h"

class AppleItem : public Items
{

public:
	AppleItem(float x, float y,int width,int height);
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~AppleItem();
};