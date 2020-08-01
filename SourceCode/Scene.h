#pragma once
#include"CGame.h"


class Scene
{
protected:

	int State;
	int mEvent;
public:
	Scene();
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	int getState();
	virtual void LoadResources() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void SetEvent(int mEvent);
	~Scene();
};
