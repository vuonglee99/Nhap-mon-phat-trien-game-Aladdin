#include "SceneManager.h"

SceneManager * SceneManager::_instance = NULL;

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

SceneManager * SceneManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new SceneManager();
	}
	return _instance;
}

void SceneManager::SetScene(Scene * x)
{
	Scene * scene_temp = mScene;
	mScene = x;
}

int SceneManager::getState()
{
	return mScene->getState();
}

void SceneManager::KeyState(BYTE * state)
{
	mScene->KeyState(state);
}

void SceneManager::OnKeyDown(int KeyCode)
{
	mScene->OnKeyDown(KeyCode);
}

void SceneManager::OnKeyUp(int KeyCode)
{
	mScene->OnKeyUp(KeyCode);
}

void SceneManager::SetEvent(int mEvent)
{
	mScene->SetEvent(mEvent);
}

void SceneManager::LoadResources()
{
	mScene->LoadResources();
}

void SceneManager::Update(DWORD dt)
{
	mScene->Update(dt);
}

void SceneManager::Render()
{
	mScene->Render();
}

