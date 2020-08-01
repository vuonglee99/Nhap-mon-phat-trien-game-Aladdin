#include "Bat.h"
#include "Aladin.h"

Bat::Bat(float x, float y, int direction)
{
	this->health = 1;
	this->x =x0= x;
	this->y = y0=y;
	this->nx = direction;
	this->type = Type::BAT;
	timeChangeDirection = GetTickCount();
	LoadResources();
}

void Bat::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture * texture = CTexture::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();


	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::ENEMY_BAT);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::DIE);
	LPANIMATION ani;

	//Idle
	sprites->Add(20000, 9, 18, 16, 34, tex);

	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);


	//attach
	sprites->Add(20001, 20, 10, 41, 32, tex);
	sprites->Add(20002, 48, 13,67,36, tex);
	sprites->Add(20003, 76,18,97,32,tex);
	sprites->Add(20004, 10,60,34,75, tex);
	sprites->Add(20005, 39,52,52,75, tex);
	sprites->Add(20006, 56,58,86,75, tex);
	sprites->Add(20007, 89,67,121,83, tex);
	sprites->Add(20008, 128,67,136,92, tex);
	sprites->Add(20009, 143,67,163,83, tex);
	sprites->Add(20010, 165,61,199,75, tex);

	ani = new CAnimation(25);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20005);
	ani->Add(20006);
	ani->Add(20007);
	ani->Add(20008);
	ani->Add(20009);
	ani->Add(20010);

	animations->Add(200, ani);
	AddAnimation(200);

	//die
	file.open("Resources/Enemy/Die.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex2);
		ani->Add(20000 + id);

	}
	animations->Add(300, ani);
	AddAnimation(300);//5
	file.close();
	
	

}

void Bat::Render()
{
	if (this->health == 0)
		if(isFinished)
			return;
	animations[state]->Render(x+10, y+7, 1, this->nx, Camera::GetInstance()->GetTranform());
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(10, 7);
	}
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->health <= 0)
	{
		if (!isFinished)
		{
			if (isSet)
			{
				isSet = false;
				dem = 0;
			}
			state = 2;
			if (animations[2]->GetCurrentFrame() == 7)
			{
				isFinished = true;
				Aladin::GetInstance()->PlusPoint(100);
			}
		}
		else
			return;
	}
	else {
		float tempX, tempY;
		Aladin::GetInstance()->GetPosition(tempX, tempY);
		if (abs(x0 - tempX) > ACTIVATE_ATTACH_STATE)
		{
			dem = 0;
			state = 0;
			this->x = x0;
			this->y = y0;
			stateMoving = 1;
			isSet = true;
		}
		else
		{
			DWORD now = GetTickCount();
			state = 1;
			switch (stateMoving)
			{
			case 0:
				dem++;
				vx = 0;
				vy = 0;
				state = 0;
				this->x = x0;
				this->y = y0;
				if (dem >= 45)
				{
					dem = 0;
					stateMoving = 1;
				}
				break;
			case 1://di sang trai
				dem++;
				vx = -0.1f;
				if (dem >= 35)
				{
					stateMoving = 2;
					dem = 0;
				}
				break;
			case 2://di sang trai nhung cham hon va di xuong
				dem++;
				vy = 0.1f;
				vx = -0.05f;
				if (dem >= 45)
				{
					stateMoving = 3;
					dem = 0;
				}
				break;

			case 3://dang di xuong va sang ben phai
				dem++;
				vy = 0.05f;
				vx = 0.05f;
				if (dem >= 60)
				{
					dem = 0;
					stateMoving = 4;
				}
				break;

			case 4://di sang phai cham va di len
				dem++;
				vx = 0.08f;
				vy = -0.04f;
				if (dem >= 65)
				{
					dem = 0;
					stateMoving = 5;
				}
				break;

			case 5://quay lai vi tri cu
				dem++;
				vx = -0.03f;
				vy = -0.07f;
				if (dem >= 55)
				{
					dem = 0;
					stateMoving = 6;
				}
				break;

			case 6:
				dem++;
				vx = -0.1f;
				vy = 0;
				if (dem >= 35)
				{
					dem = 0;
					stateMoving = 0;
				}
				break;
			}

			GameObject::Update(dt, coObjects);
			this->x += dx;
			this->y += dy;
		}
	}
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + 20;
	bottom = top + 14;
}

void Bat::SubHealth(int th)
{
}

void Bat::Revival()
{
	this->x = x0;
	this->y = y0;
	this->health = 1;
	dem = 0;
	state = 0;
	isFinished = false;
	isSet = true;
	animations[2]->SetCurrentFrame();
}

Bat::~Bat()
{
}
