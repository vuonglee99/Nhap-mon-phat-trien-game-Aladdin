#pragma once
#include "GameObject.h"


#define ACTIVATE_ATTACH_STATE 128
class Bat : public GameObject
{
	float xAladin, yAladin;
	float x0,y0;
	int state, dem = 0;
	int stateMoving;
	DWORD timeChangeDirection;
	bool isFinished, isSet = true;

public:
	Bat(float x, float y, int Direction);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SubHealth(int th);
	void Revival();
	~Bat();

};
