#pragma once
#include "GameObject.h"

class RedJewelBoard :GameObject
{
	static RedJewelBoard * _instance;
public:
	RedJewelBoard();
	~RedJewelBoard();
	void Draw();
	static RedJewelBoard * GetInstance();
	void LoadResources();
};

