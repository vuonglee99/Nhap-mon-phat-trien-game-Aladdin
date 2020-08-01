#include "AppleItem.h"

AppleItem::AppleItem(float x, float y,int width, int height)
{
	Items::Items();
	this->type = Type::APPLEITEM;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->health = 1;
	isFinished = false;
	state = 0;
	LoadResources();
}

void AppleItem::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texAladin = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::EXPLOSION);

	LPANIMATION ani;
	sprites->Add(20000, 17,3437,28,3449, texAladin);

	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(2900, ani);
	AddAnimation(2900);//0


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

void AppleItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (health == 0)
		if (!isFinished)
		{
			state = 1;
			if (animations[1]->GetCurrentFrame() == 2)
			{
				isFinished = true;
				state = 0;
			}
		}
		else
			return;
	else
		state = 0;
}

void AppleItem::Render()
{
	if (health == 0 && isFinished)
		return;
	animations[state]->Render(x + (int)width / 2, y + (int)height / 2,0,1, Camera::GetInstance()->GetTranform());
}

void AppleItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}

AppleItem::~AppleItem()
{
}
