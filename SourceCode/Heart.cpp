#include "Heart.h"

Heart::Heart(float x, float y, int width, int height)
{
	this->health = 2;
	this->type = Type::HEART;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	LoadResources();
}

void Heart::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texHeart = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 texHeart2 = texture->Get(Type::EXPLOSION);

	LPANIMATION ani;
	sprites->Add(20000, 16,3510,32,3531, texHeart);
	sprites->Add(20001, 42,3510, 59,3531, texHeart);
	sprites->Add(20002, 69,3508, 88, 3531, texHeart);

	ani = new CAnimation(100);
	ani->Add(20000);
	ani->Add(20001);
	ani->Add(20002);
	animations->Add(3300, ani);
	AddAnimation(3300);//0

	//destroy
	sprites->Add(20003, 296,46,302, 52, texHeart2);
	sprites->Add(20004, 312,32,331,52, texHeart2);
	sprites->Add(20005, 344,25,370,52, texHeart2);

	ani = new CAnimation(100);
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20005);
	animations->Add(3400, ani);
	AddAnimation(3400);

}

void Heart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	switch (health)
	{
	case 0:
		return;
	case 1:
		state = 1;
		if (animations[1]->GetCurrentFrame() == 2)
			health = 0;
		break;
	case 2:
		state = 0;
		break;
	}
}

void Heart::Render()
{
	if (health == 0)
		return;
	else
		animations[state]->Render(x + (int)width / 2, y + (int)height / 2, 0, 1, Camera::GetInstance()->GetTranform());
}

void Heart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}

Heart::~Heart()
{
}
