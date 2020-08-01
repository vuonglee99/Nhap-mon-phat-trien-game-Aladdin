#pragma once
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include "Bone.h"

using namespace std;
#define ACTIVATE_ZONE_X 164
#define ACTIVATE_ZONE_Y 64



class Skeleton : public GameObject
{
	int dem = 0;
	float x0, y0;
	int state;
	bool isFinished, isActivated, isReset = true, isDestroy;
	int toX = 0, toY = 0;

	vector<Bone *> listBone;
	Bone *mBone;
public:
	Skeleton(float x, float y, int direction);
	void LoadResources();
	void LoadBone();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Revival();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	~Skeleton();

};

