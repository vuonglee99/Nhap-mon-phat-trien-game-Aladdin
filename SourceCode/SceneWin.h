#pragma once
#include "Scene.h"
#include"SceneManager.h"
#include"SceneGame.h"
#include"Font.h"
#include"Sprite.h"
#include"Texture.h"
#include"GameObject.h"
#include "Camera.h"


class SceneWin :public Scene
{
	
	float x = 0, y = 130;
	float xG = 32, yG = 200, dx = 0;
	bool isChange;
	int nx = 1, dem=0, dem2=0,alpha=255;
		Font *mFont;
		vector<LPANIMATION> animations;
		bool isRender;
	public:
		SceneWin();
		~SceneWin();
		void KeyState(BYTE *state);
		void OnKeyDown(int KeyCode);
		void OnKeyUp(int KeyCode);
		void AddAnimation(int aniId);
		void LoadResources();
		void Update(DWORD dt);
		void Render();
};
