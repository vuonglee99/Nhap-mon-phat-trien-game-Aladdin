#include "Monkey.h"
#include "Aladin.h"
#include"Sound.h"

Monkey::Monkey(float x, float y, int direction)
{
	this->x= this->x0 = x;
	this->y=this->y0 = y;
	this->nx = direction;
	this->state = 0;
	this->type = Type::MONKEY;
	this->health = 4;
	isFinished = false;
	mSwordGuard = new SwordGuard(35,56,32);
	LoadResources();
}

void Monkey::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::GUARDS);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::DIE);
	LPANIMATION ani;


	//dung doi
	ani = new CAnimation(115);
	sprites->Add(0, 8, 175, 52, 233, tex);

	ani->Add(0);
	animations->Add(100, ani);
	AddAnimation(100);//0

	//di
	file.open("Resources/Enemy/MonkeyWalk.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(200, ani);
	AddAnimation(200);//1
	file.close();

	//bi thuong
	file.open("Resources/Enemy/MonkeyBeingHurt.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(300, ani);
	AddAnimation(300);//2
	file.close();

	//Tan cong
	file.open("Resources/Enemy/MonkeyAttach.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(400, ani);
	AddAnimation(400);//3
	file.close();

	//chet
	file.open("Resources/Enemy/Die.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex2);
		ani->Add(20000 + id);

	}
	animations->Add(500, ani);
	AddAnimation(500);//4
	file.close();

	//chet
	file.open("Resources/Enemy/Die.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex2);
		ani->Add(20000 + id);

	}
	animations->Add(600, ani);
	AddAnimation(600);//5
	file.close();
}

void Monkey::Render()
{
	if (this->health <= 0 && isFinished)
		return;
	else
	{
		toX = 0;
		toY = 85;
		float tmpX, tmpY;
		Aladin::GetInstance()->GetPosition(tmpX, tmpY);
		if (isActivated)
		{
			if (this->x - tmpX > 32)
			{
				this->nx = 1;
				toX = 0;
			}
			else
			{
				this->nx = -1;
				toX = -44;
			}
		}
		animations[state]->Render(x + toX, y + toY, 1, this->nx, Camera::GetInstance()->GetTranform(), 2);
		mSwordGuard->Render();
		if (DISPLAY_BOX == 1)
		{
			RenderBoundingBox(-23, 58);

		}
	}
}

void Monkey::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->health <= 0)
		if (!isFinished)
		{
			state = 5;
			mSwordGuard->SetState(5);
			if (animations[5]->GetCurrentFrame() == 7)
			{
				isFinished = true;
				Aladin::GetInstance()->PlusPoint(200);
			}
		}
		else
			return;
	else
	{
		float tmpX, tmpY;
		Aladin::GetInstance()->GetPosition(tmpX, tmpY);
		if (abs(tmpX - this->x0) <= ACTIVATE_ZONE && abs(tmpY - this->y0) <= 50)
		{
			isActivated = true;
			if (x0 < 2210)
				state = 1;//di
			else
				state = 0;
			vx = (tmpX - this->x) / (100 * dt);
			if (this->x - tmpX > 0)
				distanceStop = 100;
			else
				distanceStop = 50;
			if (abs(tmpX - this->x) <= distanceStop)
			{
				vx = 0;
				state = 0;
				if (this->x - tmpX > 0)
					distanceAttach = 110;
				else
					distanceAttach = 32;
				if (abs(tmpX - this->x) <= distanceAttach)
					state = 3;
			}
		}
		else
		{
			isActivated = false;
			if (abs(this->x - x0) > 5)
			{
				
				vx = (this->x0 - this->x) / (80 * dt);
				state = 1;
				if (vx > 0)
				{
					this->nx = -1;
					toX = -47;
				}
				else
					this->nx = 1;
			}
			else
			{
				state = 0;//dung doi
				vx = 0;
			}
		}
		GameObject::Update(dt,coObjects);
		if (isBeingHurt==1|| isBeingHurt == 2)
		{
			state = 2;
			if (animations[2]->GetCurrentFrame() == 8)
				isBeingHurt = -1;
		}
		if (x0 < 2210)
			CollisWithWall(coObjects);
		mSwordGuard->Update(dt, this->x, this->y, this->nx, state);
	}
	
}

void Monkey::CollisWithWall(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<LPGAMEOBJECT> listWall;
	listWall.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT cO = coObjects->at(i);
		if (coObjects->at(i)->GetType()==Type::WALL)
			listWall.push_back(coObjects->at(i));
	}

	coEvents.clear();
	coEventsResult.clear();

	CalcPotentialCollisions(&listWall, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			vx = 0;
			state = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Monkey::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 44;
	right = left + 44;
	
	top = y;
	bottom = top + 58;

}

void Monkey::Revival()
{
	this->x = this->x0;
	this->y = this->y0;
	this->state = 0;
	this->health = 4;
	isFinished = false;
	animations[2]->SetCurrentFrame();
	isBeingHurt = -1;
	animations[5]->SetCurrentFrame();
}

Monkey::~Monkey()
{
}
