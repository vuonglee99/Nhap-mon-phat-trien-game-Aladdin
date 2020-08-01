#pragma once
#include "GameObject.h"
#include "Items.h"


#define GENIE_TIME_CHANGE 175
class Genie : public Items
{
	int dem = 0;
	int state = 0;
	int isFinish = -1;
public:
	Genie(float x, float y, int width, int height);
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetFinish();
	void SubHealth();
	~Genie();
};