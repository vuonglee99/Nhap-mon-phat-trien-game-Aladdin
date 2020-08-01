#pragma once
#include"CGame.h"
#include "SceneManager.h"
#include"SceneGame.h"
#include "Keyboard.h"
#include"SceneIntro.h"

#define  MAX_FRAME_RATE 60;


class Game
{
	SceneManager *mSceneManager;
	CKeyHandler *mKeyboard;

public:

	Game();
	void GameInit(HWND);
	void LoadResources();
	void Render();
	void Update(DWORD dt);
	int Run();
	~Game();

};
