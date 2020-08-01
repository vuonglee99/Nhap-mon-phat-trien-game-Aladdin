#pragma once
#pragma once
#include "GameObject.h"
#include "SwirlFire.h"
#include "Fire.h"
#include "StaticFire.h"

#define NUM_OF_FIRE 10
class Snake :public GameObject
{
	static Snake *_instance;
	int state = 0, dem = 0, indexFire = -1;
	bool isFire1, isFire2;
	unordered_map<int, Fire *> listFire1;
	unordered_map<int, Fire *> listFire2;
	vector<int> listUpdate1;
	vector<int> listUpdate2;

public:
	Snake();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void LoadResources();
	void CollisWithAladin();
	void ReSetEveryThing();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	static Snake *GetInstance();
	~Snake();
};


