#pragma once
#pragma once
#include "Weapon.h"

#define DISTANCE_STOP 60
class Fire :public Weapon
{
	int dem = 0;
	int state = 0, index = 0;
	float x0, y0;
	bool isCollisWithAladin = false, isGetSnake_nx = false;
	int Snake_nx = 1;

public:
	Fire(float x, float y);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void CollisWithAladin();
	void CollisWithWall(vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ModifyPositionFitBoss();
	void SetState(int x);
	void Revival();
	
	~Fire();
};

