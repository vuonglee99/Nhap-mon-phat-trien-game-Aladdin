#include"Apple.h"
#include "Sound.h"

Apple::Apple()
{
	this->vx = 0.4f;
	this->vy = -0.15f;
	this->type = Type::APPLE;
	this->health = 1;
	this->x = this->y = 0;
	isFinished = true;
	LoadResources();
}

void Apple::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texAladin2 = texture->Get(Type::ALADIN2);

	LPANIMATION ani;
	ifstream file;
	int id, left, top, right, bottom, n;

	//Apple attach
	file.open("Resources/Aladin/Weapon_Apple.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin2);
		ani->Add(20000 + id);

	}
	animations->Add(2600, ani);
	AddAnimation(2600);//0
	file.close();

	//Apple destroy
	file.open("Resources/Aladin/Apple_Destroy.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin2);
		ani->Add(20000 + id);

	}
	animations->Add(2700, ani);
	AddAnimation(2700);//1
	file.close();

}

void Apple::Attach()
{

}

void Apple::Render()
{	
	if (this->health <= 0 && isFinished == true) return;
	if(state==1)
		animations[0]->SetCurrentFrame();
	animations[state]->Render(x, y, 1, 1, Camera::GetInstance()->GetTranform());

	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(4, 4);
	}
}

void Apple::SetPosition(float x, float y, int nx)
{
	if (nx == 1)
		this->x = x + 35;
	else
		this->x = x+10;
	this->y = y;
}

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(this->health<=0)
		if (!isFinished)
		{
			state = 1;
			if (animations[1]->GetCurrentFrame() == 4)
				isFinished = true;
		}
		else return;
	else {
		GameObject::Update(dt, coObjects);
		state = 0;
		vy += 0.0012*dt;
		if (state == 0)
			CollisionWithEnemy(coObjects);
		CollisionWithStaticObj(coObjects);
	}
	
}

void Apple::CollisionWithStaticObj(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> list_StaticObj;
	list_StaticObj.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == Type::BRICK ||coObjects->at(i)->GetType()==Type::WALL)
		{
			list_StaticObj.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&list_StaticObj, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0) vx = 0;
		//xet logic va cham voi brick
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			dy = 0;
			vy = 0;
			dx = 0;
			Sound::GetInstance()->Play(eSound::sound_AppleSplat);
			this->health = 0;
		}
	}
}

void Apple::CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> listEnemy;
	listEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if ((coObjects->at(i)->GetType() == Type::BAT|| coObjects->at(i)->GetType()==Type::GUARD|| coObjects->at(i)->GetType() == Type::MONKEY|| coObjects->at(i)->GetType() == Type::SKELETON|| coObjects->at(i)->GetType() == Type::BOSS || coObjects->at(i)->GetType() == Type::SNAKE)
			&& coObjects->at(i)->GetHealth()!=0)
		{
			listEnemy.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&listEnemy, coEvents);

	if (coEvents.size() == 0)
	{
		for (int i = 0; i < listEnemy.size(); i++)
		{
			LPGAMEOBJECT e = listEnemy.at(i);
			if (e->GetType() == Type::BOSS|| e->GetType() == Type::SNAKE)
			{
				if (AABBcollision(e))
				{
					e->SubHealth();
					dy = 0;
					vy = 0;
					this->health = 0;
				}
			}
		}
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0) vx = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPGAMEOBJECT e = coEventsResult.at(i)->obj;
			if (e->GetType() == Type::GUARD|| e->GetType() == Type::MONKEY)
			{
				Sound::GetInstance()->Play(eSound::sound_GuardHit);
				e->SubHealth(2);
				e->SetIsBeingHurt(1);
			}
			else if (e->GetType() == Type::SKELETON) {

				Sound::GetInstance()->Play(eSound::sound_Skeleton);
				e->SubHealth();
				e->SetIsBeingHurt(1);
			}
			else if (e->GetType() == Type::MONKEY) {

				Sound::GetInstance()->Play(eSound::sound_Iiee);
				e->SubHealth();
				e->SetIsBeingHurt(1);
			}
			else
			{
				e->SubHealth();
				e->SetIsBeingHurt(1);
			}
			dy = 0;
			vy = 0;
			this->health = 0;
		}
	}
}

void Apple::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = this->x;
	top = this->y;
	right = left + 8;
	bottom = top + 8;
}

void Apple::Revival()
{
	animations[1]->SetCurrentFrame();
	isFinished = false;
	this->health = 1;
}
Apple::~Apple()
{
}
