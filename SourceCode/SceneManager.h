#pragma once
#include "Scene.h"


class SceneManager
{
	static SceneManager * _instance;
	int State;
	Scene *mScene;

public:
	SceneManager();
	

	void SetScene(Scene * x);
	int getState();
	void SetStateSituation(int);
	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void SetEvent(int mEvent);
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	static SceneManager * GetInstance();
	~SceneManager();
};
