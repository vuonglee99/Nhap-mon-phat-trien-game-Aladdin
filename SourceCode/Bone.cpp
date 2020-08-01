#include "Bone.h"
#include "Aladin.h"
#include "Sound.h"

Bone::Bone(float x, float y, float vx, float vy,int state)
{
	this->x=this->x0 = x;
	this->y =this->y0= y;
	this->vx =vx0= vx;
	this->vy = vy0=vy;
	this->type = Type::BONE;
	this->health = 1;
	this->state =state0 =state;
	isFinished = false;
	LoadResources();
}

void Bone::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::SKELETON_IMAGE);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::EXPLOSION);

	LPANIMATION ani;
	//cuc xuong thu 1
	ani = new CAnimation(125);
	sprites->Add(0, 1009,180,1025,185, tex);
	sprites->Add(1, 1138,176,1144,191, tex);
	sprites->Add(2, 1256,177,1268,190, tex);

	ani->Add(0);
	ani->Add(1);
	ani->Add(2);
	animations->Add(100, ani);
	AddAnimation(100);//0


	ani = new CAnimation(125);
	ani->Add(0);
	ani->Add(2);
	ani->Add(1);
	animations->Add(200, ani);
	AddAnimation(200);//1

	ani = new CAnimation(125);
	ani->Add(2);
	ani->Add(1);
	ani->Add(0);
	animations->Add(300, ani);
	AddAnimation(300);//2


	sprites->Add(20011, 296, 46, 302, 52, tex2);
	sprites->Add(20012, 312, 32, 331, 52, tex2);
	sprites->Add(20013, 344, 25, 370, 52, tex2);

	ani = new CAnimation(50);
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);

	animations->Add(400, ani);
	AddAnimation(400);//3

}

void Bone::Render()
{
	if (health <= 0&&isFinished)
		return;
	animations[state]->Render(this->x, this->y, 0, 1, Camera::GetInstance()->GetTranform(), 0);
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(0, 0);
	}
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (health == 0)
		if (!isFinished)
		{
			state = 3;
			if (animations[3]->GetCurrentFrame() == 2)
				isFinished = true;
		}
		else
			return;
	else
	{
		GameObject::Update(dt, coObjects);
		vy += 0.001f*dt;
		CollisWithObj(coObjects);
		if (GetTickCount() - Aladin::GetInstance()->GetUntouchableTime() >= ALADIN_BEINGHURT_TIME)
			CollisWithAladin();
		Sound::GetInstance()->Play(eSound::sound_BonesTinkle);
	}
}

void Bone::CollisWithAladin()
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
			this->health = 0;
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
			this->health = 0;
			mAladin->SubHealth();
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
		}
	}
}

void Bone::CollisWithObj(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> list_obj;
	list_obj.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == Type::BRICK || coObjects->at(i)->GetType() == Type::MOVINGBRICK)
		{
			list_obj.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&list_obj, coEvents);
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
			LPCOLLISIONEVENT e = coEventsResult[i];
			this->health = 0;
		}
	}
}

void Bone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health > 0)
	{
		left = x;
		top = y;
		right = left + 16;
		bottom = top + 16;
	}
	else
	{
		left = top = right = bottom = 0;
	}
}

void Bone::Revival()
{
	this->x = this->x0;
	this->y = this->y0;
	this->vx = vx0;
	this->vy = vy0;
	this->health = 1;
	this->state = state0;
	isFinished = false;
	animations[3]->SetCurrentFrame();
}

Bone::~Bone()
{
}
