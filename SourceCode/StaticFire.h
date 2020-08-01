#pragma once
#pragma once
#include "Weapon.h"

#define DISTANCE_STOP 60
class StaticFire :public Weapon
{
	bool isRender;
	float tmpX, tmpY;
	int timeToBurn = 0;
public:
	StaticFire();
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void CollisWithAladin();
	~StaticFire();
};

