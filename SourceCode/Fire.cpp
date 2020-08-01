#include "Fire.h"
#include "Snake.h"
#include "Aladin.h"

Fire::Fire(float x, float y)
{
	this->nx = -1;
	this->x0 = this->x = x;
	this->y0 = this ->y = y;
	this->health = 1;
	LoadResources();
}

void Fire::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::BOSS_TEX);

	LPANIMATION ani;
	file.open("Resources/Enemy/MovingFireSnake.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//0
	file.close();
}

void Fire::Render()
{
	int toX = 0;
	if (this->nx == 1)
		toX = -75;
	if (this->health <= 0)
		return;
	animations[0]->Render(x+toX,y, 1, this->nx, Camera::GetInstance()->GetTranform(), 1);
	if (DISPLAY_BOX == 1)
		RenderBoundingBox(-37, -25);
}

void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (this->health <= 0)
		return;
	if (!isGetSnake_nx)
	{
		Snake_nx= Snake::GetInstance()->GetDirection();
		this->nx = Snake_nx;
		isGetSnake_nx = true;
	}
	CollisWithWall(coObjects);
	if (GetTickCount() - Aladin::GetInstance()->GetUntouchableTime() >= ALADIN_BEINGHURT_TIME)
		CollisWithAladin();
	

}

void Fire::CollisWithAladin()
{
	Aladin *mAladin = Aladin::GetInstance();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> Ala;
	Ala.clear();
	Ala.push_back(mAladin);

	CalcPotentialCollisions(&Ala, coEvents);

	if (coEvents.size() == 0)//co xay ra va cham
	{
		if (AABBcollision(mAladin))
		{
			mAladin->SubHealth();
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			mAladin->SubHealth();
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Fire::CollisWithWall(vector<LPGAMEOBJECT> *coObjects)
{
	//lay ds cac brick trong list object hien co
	vector<LPGAMEOBJECT> list_Wall;
	list_Wall.clear();
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == Type::WALL)
			list_Wall.push_back(coObjects->at(i));
	}

	for (int i = 0; i < list_Wall.size(); i++)
	{
		if (AABBcollision(list_Wall.at(i)))
			this->health = 0;
		else
			x += 0.5 * Snake_nx;
	}


}

void Fire::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (this->nx == -1)
		left = this->x;
	else
		left = this->x - 75;
	top = this->y;
	right = left + 16;
	bottom = top + 32;
}

void Fire::ModifyPositionFitBoss()
{
}

void Fire::SetState(int x)
{
}

void Fire::Revival()
{
	this->x = x0;
	this->y = y0;
	health = 1;
	isGetSnake_nx = false;
}


Fire::~Fire()
{
}
