#pragma once
#include "GameObject.h"

class AppleBoard :GameObject
{
	static AppleBoard * _instance;
public:
	AppleBoard();
	~AppleBoard();
	void Draw();
	static AppleBoard * GetInstance();
	void LoadResources();
};

