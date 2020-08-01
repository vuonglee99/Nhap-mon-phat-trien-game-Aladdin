#include "MovingBrick.h"
#include "Sound.h"
#include"Aladin.h"

MovingBrick::MovingBrick(float x, float y, int width, int height,int state)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->mState = state;
	this->state0 = state;
	this->type = Type::MOVINGBRICK;
	LoadResources();
}

void MovingBrick::LoadResources()
{

	ifstream file, file2;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMBrick = texture->Get(Type::Map_Object);

	LPANIMATION ani;

	file.open("Resources/Object/MovingBrick.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(10000 + id, left, top, right, bottom, texMBrick);
		ani->Add(10000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//0

	file2.open("Resources/Object/MovingBrick2.txt");
	file2 >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file2 >> id >> left >> top >> right >> bottom;
		sprites->Add(10000 + id, left, top, right, bottom, texMBrick);
		ani->Add(10000 + id);

	}
	animations->Add(200, ani);
	AddAnimation(200);//1


	//thut vao trong
	sprites->Add(10054, 996, 618, 1038, 642, texMBrick);
	ani = new CAnimation(50);
	ani->Add(10054);
	animations->Add(300, ani);
	AddAnimation(300);//2

	//thut ra ngoai
	sprites->Add(10055, 1276, 618, 1318, 642, texMBrick);
	ani = new CAnimation(25);
	ani->Add(10055);
	animations->Add(400, ani);
	AddAnimation(400);//3
}

void MovingBrick::Render()
{
	int ani_ID;
	int loop;
	switch (mState)
	{
	case 0://di ra
		ani_ID = 0;
		loop = 1;
		break;
	case 1://di vao
		ani_ID = 1;
		loop = 1;
		break;
	case 2://dung yen thut vao trong
		ani_ID = 2;
		loop = 0;
		break;
	case 3://dung yen thut ra ngoai
		ani_ID = 3;
		loop = 0;
		break;
	}

	animations[ani_ID]->Render(this->x + 21, this->y + 12, loop, this->nx, Camera::GetInstance()->GetTranform());
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(this->width / 2, this->height / 4);
	}
}

void MovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float tmpX, tmpY;
	Aladin::GetInstance()->GetPosition(tmpX, tmpY);
		switch (mState)
		{
		case 0://di ra
			if(abs(tmpX-this->x)<=160&&abs(tmpY-this->y)<=96)
				Sound::GetInstance()->Play(eSound::sound_StoneRumble);
			if (animations[0]->GetCurrentFrame() == 4)
			{
				dem = 0;
				mState = 3;
			}
			break;
		case 1://di vao
			if (animations[1]->GetCurrentFrame() == 4)
			{
				dem = 0;
				mState = 2;
			}
			break;
		case 2://dung yen thut vao trong
			dem++;
			if (dem>=80)
			{
				mState = 0;
				animations[0]->SetCurrentFrame();
			}
			break;
		case 3://dung yen thut ra ngoai
			dem++;
			if (dem >= 80)
			{
				mState = 1;
				animations[1]->SetCurrentFrame();
			}
			break;
		}
}

void MovingBrick::Reset()
{
	dem = 0;
	mState = state0;
	animations[state0]->SetCurrentFrame();
}

void MovingBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (mState==3||mState==0)
	{
		left = x;
		top = y;;
		right = left + width/2+10;
		bottom = top + height/2;
	}
	else
		left = top = right = bottom = 0;
}

MovingBrick::~MovingBrick()
{
}

