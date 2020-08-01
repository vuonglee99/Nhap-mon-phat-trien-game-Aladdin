#include "SceneWin.h"
#include "Sound.h"
SceneWin::SceneWin()
{
	this->State = Type::SCENEWIN;
	LoadResources();
}

SceneWin::~SceneWin()
{
}

void SceneWin::KeyState(BYTE * state)
{
	
}

void SceneWin::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(CGame::GetInstance()->hWnd); // thoát
}

void SceneWin::OnKeyUp(int KeyCode)
{
}

void SceneWin::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	this->animations.push_back(ani);
}

void SceneWin::LoadResources()
{

	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture * texture = CTexture::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::ALADIN);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 tex3 = texture->Get(Type::GAME_INTRO);

	// di chuyen bt
	file.open("Resources/Aladin/Win.txt");
	file >> n;
	LPANIMATION ani;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//1
	file.close();

	ani = new CAnimation(100);
	sprites->Add(20020, 513, 2851, 745, 2986, tex2);
	ani->Add(20020);
	animations->Add(200, ani);
	AddAnimation(200);//1

	// di chuyen bt
	file.open("Resources/Object/GenieFly.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex3);
		ani->Add(20000 + id);
	}
	animations->Add(300, ani);
	AddAnimation(300);//2
	file.close();
}

void SceneWin::Update(DWORD dt)
{
	Sound::GetInstance()->Play(eSound::sound_LevelComplete);
	x += 1;
	dx = 1;
	if (xG >= 300)
		isChange = true;
	else if (xG < 32) isChange = false;
	if (isChange)
	{
		dx = -1;
		nx = -1;
	}
	else
	{
		dx = 1;
		nx = 1;
	}
	xG += dx;
	if (this->x >= 180)
		isRender = true;

	if (dem > 30)
	{
		if (dem2 < 10)
		{
			alpha = 0;
			dem2++;
		}
		else
		{
			dem = 0;
			dem2 = 0;
		}
	}
	else
	{
		alpha = 255;
		dem++;
	}
}

void SceneWin::Render()
{
	int toX = 0;
	if (nx == -1)
		toX = -100;
	animations[0]->Render(x, y, 1, -1, D3DXVECTOR2(0, 0), 2);
	animations[2]->Render(xG+toX, yG, 1, nx, D3DXVECTOR2(0, 0), 2);
	if(isRender)
		animations[1]->Render(260, 150, 0, 1, D3DXVECTOR2(0, 0), 2);

	mFont->Draw(75, 150, "PUSH ESC TO EXIT", alpha);
}
