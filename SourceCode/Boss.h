#pragma once
#include "GameObject.h"
#include "SwirlFire.h"
#include "Snake.h"

#define NUM_OF_SWIRL 30
#define TIME_USING_FIRE_SWIRL 20000
class Boss :public GameObject
{
	static Boss *_instance;
	int state, dem = 0, timeDelay = 0;
	bool isChange1 = true, isChange2 = true, isRevival1 = true, isRevival2 = true,
		isUsingFireSwirl = true, isReleasedSnake, isRender = true, isSet = true;
	unordered_map<int,SwirlFire *> listSwirlFire;
	vector<int> listUpdate;

	Snake *mSnake;
	DWORD timeUsingFireSwirl = 0;
public:
	Boss();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void LoadResources();
	void CollisWithAladin();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	bool CheckSwirlFire();
	void SetHealth(int x) { this->health = x; }
	static Boss *GetInstance();
	~Boss();
};

