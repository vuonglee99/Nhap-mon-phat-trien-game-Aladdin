#include "SceneIntro.h"
#include"Sound.h"


SceneIntro::SceneIntro()
{
	this->State = SCENEINTRO;//ID cua introScene

	LoadResources();
}


SceneIntro::~SceneIntro()
{
}

void SceneIntro::KeyState(BYTE * state)
{
}

void SceneIntro::OnKeyDown(int KeyCode)
{
	/*if(y>=280)*/
		//;
	switch (sY)
	{
	case 155:
		if (KeyCode == DIK_DOWN) sY += 15;
		if(stateRender==0)
			if (KeyCode == DIK_SPACE)
				SceneManager::GetInstance()->SetScene(new SceneGame(1));
		break;
	case 170:
		if (KeyCode == DIK_DOWN) sY += 15;
		else if (KeyCode == DIK_UP) sY -= 15;
		if(stateRender==0) 
			if(KeyCode==DIK_SPACE) stateRender = 1;
			
		break;
	case 185:
		if (KeyCode == DIK_UP) sY -= 15;
		if (stateRender == 1 || stateRender == 2)
		{
			if (KeyCode == DIK_SPACE) stateRender = 0;
		}
		else if (KeyCode == DIK_SPACE) stateRender = 2;
		break;
	}
}

void SceneIntro::OnKeyUp(int KeyCode)
{
}

void SceneIntro::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	this->animations.push_back(ani);
}

void SceneIntro::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture * texture = CTexture::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::GAME_INTRO);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 tex3 = texture->Get(Type::BIRDINTRO);
	LPDIRECT3DTEXTURE9 tex4 = texture->Get(Type::SELECTOR);

	// di chuyen bt
	file.open("Resources/Object/GameIntro.txt");
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
	ani->Add(20018);
	animations->Add(200, ani);
	AddAnimation(200);//1

	ani = new CAnimation(100);
	sprites->Add(20020, 9, 12, 252, 102, tex2);
	ani->Add(20020);
	animations->Add(300, ani);
	AddAnimation(300);//1

	ani = new CAnimation(100);
	sprites->Add(20021, 139,78,220,148, tex3);
	ani->Add(20021);
	animations->Add(400, ani);
	AddAnimation(400);//1

	//selector
	ani = new CAnimation(100);
	sprites->Add(20022,0, 1, 30, 12, tex4);
	ani->Add(20022);
	animations->Add(500, ani);
	AddAnimation(500);//4

	Sound::GetInstance()->Play(eSound::sound_Skeleton);
}

void SceneIntro::Update(DWORD dt)
{
	if (stateRender!=1) sX = 120;
	else sX = 80;

	if (animations[0]->GetCurrentFrame() == 17)
	{
		state = 1;
		isRenderBird = true;
	}
	if (isRenderBird) y+= 10;
	if (y >= 240) {
		isDrawStartFont = true;
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
		
}

void SceneIntro::Render()
{
	CSprites::GetInstance()->Add(BACKGROUNDINTRO, 0, 0, 320, 256, CTexture::GetInstance()->Get(BACKGROUNDINTRO));
	CSprites::GetInstance()->Get(BACKGROUNDINTRO)->Draw(160, 75, 0, D3DXVECTOR2(0, 0), 0);
	animations[state]->Render(290, 130, 1, 1,D3DXVECTOR2(0,0),2);
	animations[2]->Render(240, 130, 1, 1, D3DXVECTOR2(0, 0), 2);
	if(isRenderBird)
		animations[3]->Render(x, y, 1, 1, D3DXVECTOR2(0, 0), 2);
	if (isDrawStartFont)
	{
		mFont->Draw(100, 130, "PUSH SPACE TO SELECT",alpha);
		animations[4]->Render(sX-20, sY, 0, 1, D3DXVECTOR2(0, 0), 0, alpha);
		switch(stateRender)
		{
		case 0:
			mFont->Draw(sX, 150, "START GAME");
			mFont->Draw(sX, 165, "HELP");
			mFont->Draw(sX, 180, "ABOUT US");
			break;

		case 1:
			mFont->Draw(sX, 150, "A OR X ATTACK ");
			mFont->Draw(sX, 165, "SPACE JUMP RIGHT LEFT RUN");
			mFont->Draw(sX, 180, "CANCEL");
			break;
		case 2:
			mFont->Draw(sX, 150, "HA THI ANH");
			mFont->Draw(sX, 165, "TRAN HUY HOANG");
			mFont->Draw(sX, 180, "LE BA VUONG CANCEL");
		}
		
	}
}
