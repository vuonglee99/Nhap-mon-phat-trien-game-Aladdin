#pragma once
#include "GameObject.h"
#include "SwordGuard.h"
#include <iostream>
#include <fstream>

using namespace std;
#define ACTIVATE_ZONE 250
#define ACTIVATE_ATTACH 150

#define GUARD_ANI_WAIT 0;
#define GUARD_ANI_WALK 1;
#define GUARD_ANI_SLAB 2//dam
#define GUARD_ANI_SLASH 3//chem
#define GUARD_ANI_BEING_HURT 4

class Guard : public GameObject
{
	int dem = 0;
	float x0, y0;
	int state, stateMoving;
	bool isFinished, isActivated;
	int toX = 0, toY = 56, distanceAttach;

	SwordGuard *mSwordGuard;
public:
	Guard(float x, float y,int direction);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Revival();
	~Guard();

};
