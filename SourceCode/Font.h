#pragma once
#include"Texture.h"
#include"CGame.h"
#include"debug.h"
class Font
{
	int left, top, right, bottom;
	static Font * _instance;
public:
	Font();
	~Font();
	static Font * GetInstance();
	void Draw(float x, float y, const string & s,int alpha=255);
	void Set(int left, int top, int right, int bottom);
};


