#pragma once
#include"GameObject.h"


class Weapon : public GameObject
{
protected:
	bool isFinished;
	DWORD lastAttach;
public:
	Weapon();
	virtual void LoadResources();
	virtual void Attach();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CheckCollision(vector<LPGAMEOBJECT>* coObjects);
	~Weapon();

};
