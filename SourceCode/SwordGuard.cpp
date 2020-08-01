#include "SwordGuard.h"
#include "Aladin.h"
#include "Sound.h"

SwordGuard::SwordGuard(int toX1,int toX2,int toY)
{
	isFinished = true;
	this->type = Type::SWORDGUARD;
	lastAttach = 0;
	this->toY = toY;
	this->toX1 = toX1;
	this->toX2 = toX2;
}

void SwordGuard::LoadResources()
{
}

void SwordGuard::Render()
{
	if (state == 5)
		return;
	if (DISPLAY_BOX==1)
	{
		if(this->nx==1)
			RenderBoundingBox(-94, 10);
		else
			RenderBoundingBox(-47, 10);
	}
}

void SwordGuard::Update(DWORD dt,float x, float y,int nx,int state)
{
	float tmpX, tmpY;
	Aladin::GetInstance()->GetPosition(tmpX, tmpY);
	if (state == 5)//con enemy no chet
		return;
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->state = state;
	ModifyPositionFitGuard();
	if (isFinished)
	{
		isFinished = false;
		if (abs(tmpX - this->x) <= 192 && abs(tmpY - this->y) <= 96&&state==3)
			Sound::GetInstance()->Play(eSound::sound_HighSword);
		dem++;
	}
	else
	{
		if (dem > 30)
		{
			isFinished = true;
			dem = 0;
		}
		else
			dem++;
	}
	if(GetTickCount()-Aladin::GetInstance()->GetUntouchableTime()>=ALADIN_BEINGHURT_TIME)
		CollisWithAladin();
	
}

void SwordGuard::CollisWithAladin()
{
	Aladin *mAladin = Aladin::GetInstance();
	if (AABBcollision(mAladin))
	{
		if (!mAladin->GetIsAttach())
		{
			mAladin->SubHealth();
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
		}
	}
}

void SwordGuard::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isFinished)
	{
		if (state == 3)
		{
			if (this->nx == 1)
			{
				left = this->x - 109;
				right = left + 40;
			}
			else
			{
				left = this->x - 54;
				right = left + 40;
			}
			top = this->y;
			bottom = top + 5;

		}
		else
			left = top = right = bottom = 0;
	}
	else
	{
		left = top = right = bottom = 0;
	}
}

void SwordGuard::ModifyPositionFitGuard()
{
	if (nx == 1)
	{
		this->x = this->x + toX1;
		this->y = this->y + toY;
	}
	else
	{
		this->x = this->x + toX2;
		this->y = this->y +toY;
	}

}

void SwordGuard::SetState(int x)
{
	this->state = x;
}

SwordGuard::~SwordGuard()
{
}
