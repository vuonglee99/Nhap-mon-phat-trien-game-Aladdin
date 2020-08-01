#pragma once
#include "GameObject.h"
#include "Items.h"

class RedJewel : public Items
{

public:
	RedJewel(float x, float y, int width, int height);
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~RedJewel();
};