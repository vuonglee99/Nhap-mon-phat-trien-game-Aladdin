#include "Boss.h"
#include "Aladin.h"
#include "Sound.h"

Boss *Boss::_instance = NULL;


Boss *Boss::GetInstance()
{
	if (_instance == NULL)
		_instance = new Boss();
	return _instance;
}

Boss::Boss()
{
	this->type = Type::BOSS;
	this->health = 25;
	this->nx = 1;
	state = 0;
	this->x = 400;
	this->y = 300;
	mSnake = Snake::GetInstance();
	for (int i = 0; i < NUM_OF_SWIRL; i++)
	{
		SwirlFire *mSwirl = new SwirlFire(0, this->x, this->y-20);
		listSwirlFire[i] = mSwirl;
	}
	timeUsingFireSwirl = GetTickCount();
	LoadResources();
}


void Boss::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::BOSS_TEX);

	LPANIMATION ani;
	ani = new CAnimation(125);
	sprites->Add(20000, 440, 11, 525, 80, tex);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);

	file.open("Resources/Enemy/Boss.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(200, ani);
	AddAnimation(200);//1
	file.close();

	//dung yen
	ani = new CAnimation(125);
	ani->Add(20001);
	animations->Add(300, ani);
	AddAnimation(300);//2

	//tha ran
	file.open("Resources/Enemy/ReleaseTheSnake.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(400, ani);
	AddAnimation(400);//3
	file.close();
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float tmpX, tmpY;
	Aladin *mAladin = Aladin::GetInstance();
	if (health <= 0)
	{
		mAladin->SetIsResetVx(true);
		return;
	}
	mAladin->GetPosition(tmpX, tmpY);
	if (isUsingFireSwirl)
	{
		if (tmpX - this->x <= 0)
		{
			state = 1;
			this->nx = -1;
			if (isRevival1)
			{
				listUpdate.clear();
				timeDelay = 0;
				for (int i = 0; i < NUM_OF_SWIRL; i++)
					listSwirlFire[i]->Revival();
			}

			if (isChange1)
			{
				dem = 0;
				animations[1]->SetCurrentFrame();
				isChange1 = false;
				isChange2 = true;
				isRevival2 = true;
				isRevival1 = false;
			}
			
			if (animations[1]->GetCurrentFrame() == 6)
			{
				dem++;
				state = 0;
				if (dem >= 160)
				{
					isChange1 = true;
					animations[1]->SetCurrentFrame();
					if (this->health>13) isRevival1 = true;
					else isUsingFireSwirl = false;
				}
			}
		}
		else
		{
			state = 1;
			this->nx = 1;
			if (isRevival2)
			{
				listUpdate.clear();
				timeDelay = 0;
				for (int i = 0; i < NUM_OF_SWIRL; i++)
					listSwirlFire[i]->Revival();
			}
			if (isChange2)
			{
				dem = 0;
				animations[1]->SetCurrentFrame();
				isChange2 = false;
				isChange1 = true;
				isRevival1 = true;
				isRevival2 = false;
			}
			
			if (animations[1]->GetCurrentFrame() == 6)
			{
				state = 0;
				dem++;
				if (dem >= 160)
				{
					isChange2 = true;
					animations[1]->SetCurrentFrame();
					if (this->health > 13) isRevival2 = true;
					else isUsingFireSwirl = false;
				}
			}
		}
		if (GetTickCount() - mAladin->GetUntouchableTime() >= ALADIN_BEINGHURT_TIME)
			CollisWithAladin();
		if (timeDelay == 0)
		{
			listUpdate.push_back(0);
			timeDelay++;
		}
		else
			timeDelay++;
		if (timeDelay % 5 == 0)
		{
			int tmp = timeDelay / 5;
			if (tmp < NUM_OF_SWIRL) listUpdate.push_back(tmp);
		}

		for (int i = 0; i < listUpdate.size(); i++)
			listSwirlFire[listUpdate.at(i)]->Update(dt, coObjects);

		if (CheckSwirlFire()) mAladin->SetIsResetVx(true);
	}
	else
	{
		if (GetTickCount() - mAladin->GetUntouchableTime() >= ALADIN_BEINGHURT_TIME)
			CollisWithAladin();
		state = 3;
		if (animations[3]->GetCurrentFrame() == 6) {
			isReleasedSnake = true;
			isRender = false;
			state = 0;
			if (isSet)
			{
				mSnake->SetHealth(12);
				isSet = false;
			}
		}
		if (isReleasedSnake) mSnake->Update(dt, coObjects);
		if (mSnake->GetHealth() <= 0&&isReleasedSnake) this->health = 0;
	}
}

void Boss::Render()
{
	if (health <= 0)
		return;
	if(isRender)
		animations[state]->Render(this->x,this->y, 1, this->nx, Camera::GetInstance()->GetTranform(), 0);

	for (int i = 0; i < listUpdate.size(); i++)
		listSwirlFire[listUpdate.at(i)]->Render();

	if (isReleasedSnake)
		mSnake->Render();

	if (DISPLAY_BOX == 1)
	{
		if(this->nx==-1)
			RenderBoundingBox(-20,0);
		else
			RenderBoundingBox(0, 0);
	}
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isRender)
	{
		if (this->nx == -1) left = this->x - 20;
		else left = this->x - 32;
		right = left + 64;
		top = this->y;
		bottom = top + 71;
	}
	else
		left = top = right = bottom = 0;
}
bool Boss::CheckSwirlFire()
{
	for (int i = 0; i < NUM_OF_SWIRL; i++)
		if(listSwirlFire[i]->GetHealth() != 0)
			return false;
	return true;
}
Boss::~Boss()
{
	
}
void Boss::CollisWithAladin()
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
			mAladin->SubHealth(2);
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
			Sound::GetInstance()->Play(eSound::sound_JafarLaugh);
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			mAladin->SubHealth(2);
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
			Sound::GetInstance()->Play(eSound::sound_JafarLaugh);
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}