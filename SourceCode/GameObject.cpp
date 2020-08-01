#include "GameObject.h"


GameObject::GameObject()
{
	x = 0;
	y = 0;
	vx = 0;
    vy = 0;
	nx = 1;
}

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	this->animations.push_back(ani);
}

Type GameObject::GetType()
{
	return this->type;
}

void GameObject::SetID(int id)
{
	this->id = id;
}

int GameObject::GetID()
{
	return this->id;
}

void GameObject::SetDirection(int Direction)
{
	this->nx = Direction;
}

int GameObject::GetDirection()
{
	return this->nx;
}

void GameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void GameObject::SetSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}

void GameObject::LoadAni()
{

}

void GameObject::Reset()
{

}

void GameObject::Revival()
{
}

GameObject::~GameObject()
{

}

void GameObject::Update(DWORD dt , vector<LPGAMEOBJECT>* coObject)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void GameObject::Render()
{

}

void GameObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);//chua ket qua cua viec xet  va cham bao gom:
	//1 obj duoc dem xet va cham voi doi tuong this, huong, tg bd va cham
	return e;
}

//tien doan va cham
void GameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents)
{
	//coObjects la ds cac obj duoc dem di xet va cham voi doi tuong this
	for (UINT i = 0; i < coObjects->size(); i++)//xet lan luot cac obj do
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)//thoa man thi co the xay ra va cham
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void GameObject::FilterCollision(vector<LPCOLLISIONEVENT> &coEvents,vector<LPCOLLISIONEVENT> &coEventsResult,float &min_tx, float &min_ty,float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0)
		{
			min_tx = c->t;//tg khi nao se xay ra va cham
			nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

bool GameObject::AABBcollision(LPGAMEOBJECT gameobj)
{
	RECT rect1, rect2;
	float left, top, right, bottom;
	gameobj->GetBoundingBox(left, top, right, bottom);
	rect1.left = left;
	rect1.top = top;
	rect1.right = right;
	rect1.bottom = bottom;
	this->GetBoundingBox(left, top, right, bottom);
	rect2.left = left;
	rect2.top = top;
	rect2.right = right;
	rect2.bottom = bottom;
	return Camera::GetInstance()->isContain(rect1, rect2);
}

void GameObject::RenderBoundingBox(int toX,int toY)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTexture::GetInstance()->Get(Type::BOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x+toX, y+toY, bbox, rect.left, rect.top, rect.right, rect.bottom,0,Camera::GetInstance()->GetTranform());
}
