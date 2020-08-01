#include "SwirlFire.h"
#include "Aladin.h"
#include "Boss.h"

SwirlFire::SwirlFire(int index,float x,float y)
{
	this->index = index;
	this->x =x0=x;
	this->y=y0= y;
	this->health = 1;
	isFinished = false;
	LoadResources();
}

void SwirlFire::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::BOSS_TEX);

	LPANIMATION ani;
	ani = new CAnimation(25);
	sprites->Add(20000, 198, 425, 226, 439, tex);
	sprites->Add(20001, 238, 423, 262, 439, tex);
	sprites->Add(20002, 270, 424, 296, 439, tex);
	ani->Add(20000);
	ani->Add(20001);
	ani->Add(20002);
	animations->Add(100, ani);
	AddAnimation(100);

	ani = new CAnimation(25);
	sprites->Add(20003, 310,426,324,439, tex);
	sprites->Add(20004, 334,431,352,439, tex);
	sprites->Add(20005,382,418,397,439, tex);
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20005);
	animations->Add(200, ani);
	AddAnimation(200);

}

void SwirlFire::Render()
{
	if (health == 0&&isFinished)
		return;
	animations[state]->Render(x , y, 1, 1, Camera::GetInstance()->GetTranform(), 0);
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(0, 0);
	}

}

void SwirlFire::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float tmpX, tmpY, bX, bY, Ala_Vx, Ala_Vy;

	Aladin* mAladin = Aladin::GetInstance();
	mAladin->GetPosition(tmpX, tmpY);
	mAladin->GetSpeed(Ala_Vx, Ala_Vy);
	int Ala_nx = mAladin->GetDirection();

	Boss *mBoss = Boss::GetInstance();
	mBoss->GetPosition(bX, bY);
	if (health == 0) {
		mAladin->SetChangeVx(1);
		//isCollisWithAladin = false;
		if (!isFinished) {
			state = 1;
			if (animations[1]->GetCurrentFrame() == 2) {
				isFinished = true;

			}
		}
		else
			return;
	}

	if (Ala_nx == -1)
		this->vx = ((tmpX - 18) - this->x) / (5 * dt);
	else
		this->vx = (tmpX - this->x) / (5 * dt);
	this->vy = (tmpY - this->y) / (5 * dt);

	if (Ala_Vx > 0)
		vx += 0.08f;
	else
		if (Ala_Vx < 0)
			vx -= 0.08f;

	CollisWithAladin();
	if (isCollisWithAladin)
	{
		if (Ala_Vx != 0)
		{
			mAladin->SetIsResetVx(false);
			if (Ala_Vy == 0)
			{
				if (bX - tmpX > DISTANCE_STOP) {//dang o phia ben trai
					if (Ala_nx == -1)
					{
						mAladin->SetChangeVx(-1.2f);
						mAladin->SetState(ALADIN_WALKING_LEFT_STATE);
					}
					else
					{
						mAladin->SetChangeVx(0.8f);
						mAladin->SetState(ALADIN_WALKING_RIGHT_STATE);
					}

				}
				else if (tmpX - bX > (DISTANCE_STOP - 25)) {
					if (Ala_nx == 1)
					{
						mAladin->SetChangeVx(-1.2f);
						mAladin->SetState(ALADIN_WALKING_RIGHT_STATE);
					}
					else
					{
						mAladin->SetChangeVx(0.8f);
						mAladin->SetState(ALADIN_WALKING_LEFT_STATE);
					}
				}
				else
					mAladin->SetIsResetVx(true);
			}
			else mAladin->SetIsBusy(true);

		}
		else //dung yen
			if (bX - tmpX > DISTANCE_STOP)//dang o ben trai so voi boss
			{
				if (Ala_nx == -1)
				{
					mAladin->SetChangeVx(-1.2f);
					mAladin->SetState(ALADIN_WALKING_LEFT_STATE);
				}
				else
				{
					mAladin->SetChangeVx(0.5f);
					mAladin->SetState(ALADIN_WALKING_RIGHT_STATE);
				}
			}
			else if (tmpX - bX > (DISTANCE_STOP - 25)) {
				if (Ala_nx == 1)
				{
					mAladin->SetChangeVx(-1.2f);
					mAladin->SetState(ALADIN_WALKING_RIGHT_STATE);
				}
				else
				{
					mAladin->SetChangeVx(-0.5f);
					mAladin->SetState(ALADIN_WALKING_LEFT_STATE);
				}
			}
	}
	GameObject::Update(dt, coObjects);

	
}

void SwirlFire::CollisWithAladin()
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
			isCollisWithAladin = true;
			this->health = 0;
		}
		else {
			x += dx;
			y += dy;
			isCollisWithAladin = false;
		}

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			isCollisWithAladin = true;
			this->health = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void SwirlFire::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = this->x;
	top = this->y;
	right = left + 25;
	bottom = top + 15;
}

void SwirlFire::ModifyPositionFitBoss()
{
}

void SwirlFire::SetState(int x)
{
}

void SwirlFire::Revival()
{
	health = 1;
	this->x = x0;
	this->y = y0;
	vx = vy = 0;
	state = 0;
	isFinished = false;
	animations[1]->SetCurrentFrame();
}

SwirlFire::~SwirlFire()
{
}
