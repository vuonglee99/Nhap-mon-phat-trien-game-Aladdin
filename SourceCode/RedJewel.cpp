#include "RedJewel.h"

RedJewel::RedJewel(float x, float y, int width, int height)
{
	Items::Items();
	this->type = Type::REDJEWEL;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	state = 0;
	LoadResources();
}

void RedJewel::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texAladin = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::EXPLOSION);

	LPANIMATION ani;
	sprites->Add(20000, 49,3435,66,3451, texAladin);
	sprites->Add(20001, 76,3435,93,3451, texAladin);
	sprites->Add(20002, 103,3435,120, 3451, texAladin);
	sprites->Add(20003, 130,3435,147,3451, texAladin);
	sprites->Add(20004, 157,3434,174, 3451, texAladin);
	sprites->Add(20005, 184,3431,216,3452, texAladin);
	sprites->Add(20006, 226,3433,249,3451, texAladin);
	sprites->Add(20007, 258,3435,275,3451, texAladin);
	sprites->Add(20008, 285,3435,302,3451, texAladin);

	ani = new CAnimation(100);
	ani->Add(20000);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20005);
	ani->Add(20006);
	ani->Add(20007);
	ani->Add(20008);
	animations->Add(3000, ani);
	AddAnimation(3000);//0


	sprites->Add(20011, 296, 46, 302, 52, tex2);
	sprites->Add(20012, 312, 32, 331, 52, tex2);
	sprites->Add(20013, 344, 25, 370, 52, tex2);

	ani = new CAnimation(50);
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);

	animations->Add(100, ani);
	AddAnimation(100);

}

void RedJewel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (health == 0)
		if (!isFinished)
		{
			state = 1;
			if (animations[1]->GetCurrentFrame() == 2)
				isFinished = true;
		}
		else
			return;
	else
		state = 0;
}

void RedJewel::Render()
{
	if (this->health == 0&&isFinished)
		return;
	animations[state]->Render(x + (int)width / 2, y + (int)height / 2, 0, 1, Camera::GetInstance()->GetTranform(),0);
}

void RedJewel::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}

RedJewel::~RedJewel()
{
}
