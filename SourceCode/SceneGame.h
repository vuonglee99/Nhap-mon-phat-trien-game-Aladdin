#pragma once
#include"Scene.h"
//#include"CGame.h"
#include "Aladin.h"
#include "GameMap.h"
#include "Camera.h"
#include "Keyboard.h"
#include"Grid.h"
#include"MapObject.h"
#include "Board.h"
#include "SceneBoss.h"
#include "Sound.h"
#include "SceneGameOver.h"


#define ALADIN_NORMAL 1
#define ALADIN_DIE 0
#define ALADIN_OVER -1
class SceneGame :public Scene
{

	Aladin *mAladin;
	GameMap *mGamemap1, *mGamemap2, *mGamemap3, *mGamemap4, *mGamemap5;
	GameMap *mGamemap6, *mGamemap7, *mGamemap8, *mGamemap9, *mGamemap10;
	MapObject *mMapObject;
	Camera *mCamera;
	Grid *mGrid;
	Board *mBoard;
	bool isRunning;
	DWORD  time;
	bool isTransitionScene;
	float xTrans, yTrans;
	Sound *mSound;
	vector<LPGAMEOBJECT> obj;
public:
	SceneGame();
	SceneGame(int State);
	~SceneGame();
	void LoadResources();
	void SetEvent(int mEvent);
	void Render();
	void Update(DWORD dt);
	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

