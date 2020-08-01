#pragma once
#include "GameObject.h"
#include "Items.h"

class RestartPoint : public Items
{
	int state = 0;

public:
	RestartPoint(int id, float x, float y, int width, int height);
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~RestartPoint();
};