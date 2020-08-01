#pragma once
#include "Weapon.h"

class SwordGuard :public Weapon
{
	int dem = 0;
	int state, toY, toX1,toX2;
public:
	SwordGuard(int toX1,int toX2,int toY);
	void LoadResources();
	void Render();
	void Update(DWORD dt,float x, float y,int nx,int state);
	void CollisWithAladin();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ModifyPositionFitGuard();
	void SetState(int x);
	~SwordGuard();
};
