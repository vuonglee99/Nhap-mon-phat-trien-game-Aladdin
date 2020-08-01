#pragma once
#pragma once
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include "SwordGuard.h"

using namespace std;
#define ACTIVATE_ZONE 164
#define ACTIVATE_ATTACH 150



class Monkey : public GameObject
{
	int dem = 0;
	float x0, y0;
	int state, defaultLocation, isMove;
	bool isFinished, isActivated;
	int toX = 0, toY = 56, distanceAttach, distanceStop;
	SwordGuard *mSwordGuard;
public:
	Monkey(float x, float y, int direction);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void CollisWithWall(vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Revival();
	~Monkey();

};


