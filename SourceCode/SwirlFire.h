#pragma once
#include "Weapon.h"

#define DISTANCE_STOP 60
class SwirlFire :public Weapon
{
	int dem = 0;
	int state = 0, index = 0;
	float x0, y0;
	bool isCollisWithAladin = false;

public:
	SwirlFire(int index,float x, float y);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void CollisWithAladin();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ModifyPositionFitBoss();
	void SetState(int x);
	void Revival();
	~SwirlFire();
};

