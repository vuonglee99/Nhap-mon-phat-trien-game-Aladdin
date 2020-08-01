#include "Game.h"


void Game::GameInit(HWND hWnd)
{
	CGame::GetInstance()->Init(hWnd);
	mSceneManager = SceneManager::GetInstance();
	mSceneManager->SetScene(new SceneIntro());
	mKeyboard = CKeyHandler::GetInstance();
}

Game::Game()
{

}

void Game::LoadResources()
{


}


void Game::Update(DWORD dt)
{

	mSceneManager->Update(dt);
}

void Game::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3dDevice();
	LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->Getbackbuffer();
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(106, 148, 189, 1), 0.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		mSceneManager->Render();
		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

int Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 500/ MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			mKeyboard->ProcessKeyBoard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

Game::~Game()
{

}

