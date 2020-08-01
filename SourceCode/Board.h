#pragma once
#include "HealthBoard.h"
#include "Aladin.h"
#include "RedJewelBoard.h"
#include "AppleBoard.h"
#include "Font.h"
#include<iostream>
#include <iomanip>
#include <string>

using namespace std;

class Board
{
	static Board * _instance;
	HealthBoard *mHealthBoard;
	RedJewelBoard *mRedJewelBoard;
	AppleBoard *mAppleBoard;
	Font *mFont;
	int aladinHealth;
	int numRedJewel;
	int numApple;
	int point;
	int life;
	string FillNumber(string s, UINT MaxNumber);
public:
	Board();
	void Render();
	void Update();
	void LoadAni();
	static Board * GetInstance();
	~Board();

};
