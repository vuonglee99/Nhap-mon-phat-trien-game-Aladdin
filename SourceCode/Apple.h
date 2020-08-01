#pragma once
#include"GameObject.h"
#include "Weapon.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
#include"Camera.h"
#include "Bat.h"



using namespace std;


#define APPLE_ANI_ATTACH 0
#define APPLE_ANI_DESTROY 1


class Apple : public Weapon
{
	bool  isplay, isFinish;
	int state, demSubGuard = -1;
public:
	Apple();
	void LoadResources();
	void Attach();
	void Render();
	void SetPosition(float x, float y, int nx);
	void SetSpeed(int x)
	{
		this->vx = 0.33f*x;
		this->vy = -0.1f;
	}

	void SetIsFinish()
	{
		this->isFinish = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void CollisionWithStaticObj(vector<LPGAMEOBJECT>* coObjects);
	void CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Revival();
	~Apple();
};