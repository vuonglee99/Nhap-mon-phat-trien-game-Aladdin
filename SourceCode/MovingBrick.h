#pragma once
#include "GameObject.h"
#include "Aladin.h"
#include"Texture.h"
#include"Sprite.h"
#include "define.h"
#include"Camera.h"
#include <fstream>
#include"debug.h"
#include<tchar.h>

using namespace std;

class MovingBrick : public GameObject
{
	int mState, state0, dem = 0, delay = 0;
	DWORD t = 0;
	int isCollis;
	bool isReset;
	int width, height;
public:
	MovingBrick(float x, float y, int width, int height,int state);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Reset();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	~MovingBrick();
};




