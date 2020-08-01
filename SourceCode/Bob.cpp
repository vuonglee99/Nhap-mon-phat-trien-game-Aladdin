#include "Bob.h"

Bob::Bob(float x, float y, int width, int height,int state)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	mState = state;
	state0 = state;
	this->type = Type::BOB;
	LoadResources();
}

void Bob::LoadResources()
{

	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texBob= texture->Get(Type::Map_Object);

	LPANIMATION ani;
	
	file.open("Resources/Object/Bob.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(10000+id, left, top, right, bottom, texBob);
		ani->Add(10000+id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//0
	file.close();

	file.open("Resources/Object/Bob2.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(10000 + id, left, top, right, bottom, texBob);
		ani->Add(10000 + id);

	}
	animations->Add(200, ani);
	AddAnimation(200);//1
	file.close();
}

void Bob::Render()
{

	animations[mState]->Render(this->x + 16.5, this->y + 33.5, 1, this->nx, Camera::GetInstance()->GetTranform());
	if (mState == 0)
		if (animations[mState]->GetCurrentFrame() == 14 || animations[mState]->GetCurrentFrame() == 15)
			isCollis = 1;
		else
			isCollis = 0;
	else
		isCollis = 0;

	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(this->width / 4, this->height / 2);
	}
	
}

void Bob::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	switch (mState)
	{
	case 0:
		if (animations[0]->GetCurrentFrame() == 14)
		{
			mState = 1;
			animations[1]->SetCurrentFrame();
		}
		break;
	case 1:
		if (animations[1]->GetCurrentFrame() == 13)
		{
			mState = 0;
			animations[0]->SetCurrentFrame();
		}
		break;
	case 2:
		mState = 0;
		animations[0]->SetCurrentFrame(8);
		break;
	}
}

void Bob::StartCountingTime(DWORD & t)
{
}

void Bob::Reset()
{
	mState = state0;
	animations[state0]->SetCurrentFrame();
}

void Bob::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	switch (isCollis)
	{
	case 0:
		left = top = right = bottom = 0;
		break;
	case 1:
		left = x;
		top = y;
		right = left + width/2;
		bottom = top + height;
	}
}

Bob::~Bob()
{
}
