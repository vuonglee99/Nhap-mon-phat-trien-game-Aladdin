#include "Genie.h"
#include "Aladin.h"

Genie::Genie(float x, float y, int width, int height)
{
	this->health = 2;
	this->type = Type::GENIE;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	LoadResources();
}

void Genie::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texGenie = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 texGenie2 = texture->Get(Type::EXPLOSION);

	LPANIMATION ani;
	sprites->Add(20000,328,3440,376,3490, texGenie);

	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(3200, ani);
	AddAnimation(3200);//0


	sprites->Add(20001,376,3438,419,3490, texGenie);
	sprites->Add(20002, 429,3446,472,3490, texGenie);
	sprites->Add(20003, 482,3446,527, 3490, texGenie);

	ani = new CAnimation(125);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(3300, ani);
	AddAnimation(3300);//1

	file.open("Resources/Object/GenieDestroy.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texGenie2);
		ani->Add(20000 + id);

	}
	animations->Add(3400, ani);
	AddAnimation(3400);//2
	file.close();
}

void Genie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	switch (health)
	{
	case 0:
		return;
	case 1:
		state = 2;
		if (animations[2]->GetCurrentFrame() == 24)
		{
			health = 0;
			Aladin::GetInstance()->PlusPoint(100);
		}
		break;
	case 2:
		if (state == 0)
		{
			dem++;
			if (dem >= GENIE_TIME_CHANGE)
			{
				state = 1;
				dem = 0;
				animations[1]->SetCurrentFrame();
			}
		}
		else
		{
			if (animations[1]->GetCurrentFrame() == 2)
				state = 0;
		}
		break;
	}
	
}

void Genie::Render()
{
	if (this->health == 0)
		return;
	else
		animations[state]->Render(x + (int)width / 2, y + (int)height / 2, 0, 1, Camera::GetInstance()->GetTranform());
}

void Genie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}

void Genie::SetFinish()
{
	isFinish = 1;
}

void Genie::SubHealth()
{
	this->health = 1;
}

Genie::~Genie()
{
}
