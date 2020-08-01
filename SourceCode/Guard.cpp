#include "Guard.h"
#include "Aladin.h"
#include "Sound.h"

Guard::Guard(float x, float y,int direction)
{
	this->health = 4;
	this->type = Type::GUARD;
	this->x=this->x0 = x;
	this->y0=this->y = y;
	this->nx = direction;
	mSwordGuard = new SwordGuard(24,64,5);
	isFinished = false;
	LoadResources();
}

void Guard::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture * texture = CTexture::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();


	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::GUARDS);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::DIE);
	LPANIMATION ani;

	file.open("Resources/Enemy/GuardWait.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//0
	file.close();

	//di
	file.open("Resources/Enemy/GuardWalk.txt");
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

	//dam
	file.open("Resources/Enemy/GuardSlab.txt");
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

	//chem
	file.open("Resources/Enemy/GuardSlash.txt");
	file >> n;
	ani = new CAnimation(75);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(400, ani);
	AddAnimation(400);//3
	file.close();

	//bi thuong do tao
	file.open("Resources/Enemy/GuardBeingHurt.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
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

	//bi thuong do dam
	file.open("Resources/Enemy/GuardBeingStabbed.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(700, ani);
	AddAnimation(700);//4
	file.close();

}

void Guard::Render()
{
	if (this->health <= 0&&isFinished)
		return;
	else
	{
		int formSize = 2;
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
				toX = -47;
			}
		}

		animations[state]->Render(x + toX, y + toY, 1, this->nx, Camera::GetInstance()->GetTranform(), formSize);
		mSwordGuard->Render();
		if (DISPLAY_BOX == 1)
		{
			RenderBoundingBox(-23, 28);

		}
	}
}

void Guard::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float tmpX, tmpY;
	Aladin::GetInstance()->GetPosition(tmpX, tmpY);
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
		if (abs(tmpX - this->x0) <= ACTIVATE_ZONE && abs(tmpY - this->y0) <= 50)
		{
			dem = 0;
			isActivated = true;
			state = 1;
			vx = (tmpX - this->x) / (80 * dt);
			if (this->x - tmpX > 0)
				distanceAttach = 175;
			else
				distanceAttach = 64;
			if (abs(tmpX - this->x) <= distanceAttach)
			{
				vx = 0;
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
				dem++;
				state = 0;//dung doi
				vx = 0;
				if (abs(tmpX - this->x) <= 192 && abs(tmpY - this->y) <= 96&&dem%10==0)
					Sound::GetInstance()->Play(eSound::sound_GuardBeckon);
			}
		}
		GameObject::Update(dt, coObjects);
		if (isBeingHurt==1)
		{
			state = 4;
			if (animations[4]->GetCurrentFrame() == 8)
				isBeingHurt = -1;
		}
		else if (isBeingHurt == 2)
		{
			state = 6;
			if (animations[6]->GetCurrentFrame() == 5)
				isBeingHurt = -1;
		}
		mSwordGuard->Update(dt, this->x, this->y, this->nx, state);
		x += dx;
	}
}


void Guard::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	if (this->nx == 1)
	{
		left = x -47;
		right = left + 47;
	}
	else
	{
		left = x-47 ;
		right = left + 47;
	}
	top = y;
	bottom = top + 56;
}

void Guard::Revival()
{
	this->health = 4;
	this->x0 = x;
	this->y0 = y;
	isFinished = false;
	animations[5]->SetCurrentFrame();
	animations[6]->SetCurrentFrame();
	animations[4]->SetCurrentFrame();
	isBeingHurt = -1;
}


Guard::~Guard()
{
}
