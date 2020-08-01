#pragma once
#include"Gameobject.h"
#include "Camera.h"

class Items : public GameObject
{
protected:
	int width, height, state;
	bool isFinished;
public:
	Items();
	Items(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	bool GetIsFinished();
	virtual void SetFinish();
	~Items();
};
