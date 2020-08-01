#include "SceneGameOver.h"
#include "Sound.h"

SceneGameOver::SceneGameOver()
{
	this->TimeBling = 0;
	this->TimeBetweenBling = 0;
	this->isDrawEndFont = true;
	LoadResources();
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::KeyState(BYTE * state)
{
}

void SceneGameOver::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(CGame::GetInstance()->hWnd); // thoát
	else
	{
		this->isPressedKey = true;
	}
}

void SceneGameOver::OnKeyUp(int KeyCode)
{
}

void SceneGameOver::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	this->animations.push_back(ani);
}

void SceneGameOver::LoadResources()
{

	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture * texture = CTexture::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 texAladin = texture->Get(Type::ALADIN);
	LPDIRECT3DTEXTURE9 texAladin3 = texture->Get(Type::ALADIN3);

	// di chuyen bt
	
	
	LPANIMATION ani;
	ani = new CAnimation(100);
	file.open("Resources/Aladin/Death.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin3);
		ani->Add(20000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//27
	file.close();
	

	ani = new CAnimation(100);
	file.open("Resources/Aladin/Death2.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(200, ani);
	AddAnimation(200);//27
	file.close();
}

void SceneGameOver::Update(DWORD dt)
{
	if (animations[0]->GetCurrentFrame() == 33)
	{
		state = 1;
	}
	if (isPressedKey)
	{
		SceneManager::GetInstance()->SetScene(new SceneGame(2));
		
	}

}

void SceneGameOver::Render()
{
	mFont->Draw(120, 30, "GAME OVER");
	if (isDrawEndFont)
	{
		mFont->Draw(50, 130, "PUSH START OR ESC TO EXIT");
	}
	animations[state]->Render(180, 120, 1, 1, D3DXVECTOR2(0, 0), 2);
}
