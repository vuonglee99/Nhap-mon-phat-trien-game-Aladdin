#pragma once
#include "GameObject.h"
#include "Aladin.h"
#include"Texture.h"
#include"Sprite.h"
#include "define.h"
#include"Camera.h"
#include <fstream>

using namespace std;




#define ARROW_ACTIVATE 128
#define ARROW_IDLE_TIME 3500//ben trong
#define ARROW_IDLE_TIME2 1000//ben ngoai

class Arrow : public GameObject
{

	int mState , dem;
	DWORD t=0;
	bool isCounting = true;
	int width, height;
public:
	Arrow(float x, float y,int width,int height,int state);
	void LoadResources();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void StartCountingTime(DWORD &t);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	~Arrow();
};
