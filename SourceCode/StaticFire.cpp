#include "StaticFire.h"
#include "Snake.h"
#include "Aladin.h"

StaticFire::StaticFire()
{

	LoadResources();
}

void StaticFire::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::BOSS_TEX);

	LPANIMATION ani;
	ani = new CAnimation(50);
	file.open("Resources/Enemy/StaticFireSnake.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//3
	file.close();
}

void StaticFire::Render()
{ 
	if (!isRender) return;
	animations[0]->Render(tmpX, tmpY, 1, this->nx, Camera::GetInstance()->GetTranform(), 1);
	if (DISPLAY_BOX == 1)
		RenderBoundingBox(-37, -25);
}

void StaticFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Aladin *mAladin = Aladin::GetInstance();
	if (mAladin->GetIsCollisWithBrick()&&mAladin->GetVx()==0&& Snake::GetInstance()->GetHealth() > 0)
	{
		if (timeToBurn >= 100)
		{
			mAladin->GetPosition(tmpX, tmpY);
			tmpY += 50;
			tmpX += 5;
			isRender = true;
			if (GetTickCount() - mAladin->GetUntouchableTime() >= ALADIN_BEINGHURT_TIME)
				CollisWithAladin();
		}
		else timeToBurn++;
	}
	else {
		isRender = false;
		timeToBurn = 0;
		return;
	}
}

void StaticFire::CollisWithAladin()
{
	Aladin *mAladin = Aladin::GetInstance();
	mAladin->SubHealth();
	mAladin->SetIsBeingHurt();
	mAladin->StartUntouchableTime();
}

StaticFire::~StaticFire()
{
}

