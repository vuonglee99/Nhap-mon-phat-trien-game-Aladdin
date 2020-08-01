#pragma once
//#include "Sprite.h"
//#include "Texture.h"
//#include "CGame.h"
#include "GameObject.h"



class HealthBoard:public GameObject
{
	static HealthBoard * _instance;
public:
	HealthBoard();
	~HealthBoard();
	void Draw(int AladinHealth);
	static HealthBoard * GetInstance();
	void LoadResources();
};
