#include "RestartPoint.h"
#include "Aladin.h"

RestartPoint::RestartPoint(int id, float x, float y, int width, int height)
{
	this->id = id;
	this->health = 1;
	this->type = Type::RESTARTPOINT;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	isFinished = false;
	LoadResources();
}

void RestartPoint::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::ITEM);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::ALADIN);

	LPANIMATION ani;
	sprites->Add(20000, 19,424,39,457, tex);

	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);//0

	//destroy
	sprites->Add(20001, 49,428,73,457, tex);
	sprites->Add(20002, 78,437,112,457, tex);
	sprites->Add(20003, 119,425,139,459, tex);
	sprites->Add(20004, 145, 425,168,459, tex);
	sprites->Add(20005, 174,426, 200,459, tex);
	sprites->Add(20006, 207,426, 231,460, tex);
	sprites->Add(20007, 239,427, 259,461, tex);
	sprites->Add(20008, 270,428, 294,461, tex);
	sprites->Add(20009, 302,429, 325,462, tex);


	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20005);
	ani->Add(20006);
	ani->Add(20007);
	ani->Add(20008);
	ani->Add(20009);

	animations->Add(200, ani);
	AddAnimation(200);//1

	sprites->Add(20009, 302, 429, 325, 462, tex);
	ani = new CAnimation(100);
	ani->Add(20009);
	animations->Add(300, ani);
	AddAnimation(300);//2

	file.open("Resources/Aladin/AladinRestart.txt");
	file >> n;//18
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex2);
		ani->Add(20000 + id);

	}
	animations->Add(400, ani);
	AddAnimation(400);//1
	file.close();



}

void RestartPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (health == 0)
		if (!isFinished)
		{
			state = 1;
			if (animations[1]->GetCurrentFrame() == 8)
			{
				state = 2;
				isFinished = true;
			}
		}
		else
			return;
	else
		state = 0;
}

void RestartPoint::Render()
{
	int form = 0;
	int toX = 0, toY = 0;
	Aladin *mAladin = Aladin::GetInstance();
	/*if (mAladin->GetIsRestart())
		if (mAladin->GetIdRestartPoint() == this->id)
		{
			state = 3;
			form = 2;
			if (animations[3]->GetCurrentFrame() == 13)
			{
				mAladin->SetIsRestart(false);
				state = 2;
				form = 0;
			}
		}*/

	if (form == 0)
	{
		toX = (int)width / 2;
		toY = (int)height / 2;
	}
	else
	{
		toX = width;
		toY = height;
	}
	animations[state]->Render(x  +toX, y +toY, 1, 1, Camera::GetInstance()->GetTranform(),form);
}

void RestartPoint::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}

RestartPoint::~RestartPoint()
{
}
