#include "Snake.h"
#include "Aladin.h"
#include "Sound.h"
#include "Boss.h"

Snake *Snake::_instance = NULL;

Snake *Snake::GetInstance()
{
	if (_instance == NULL)
		_instance = new Snake();
	return _instance;
}

Snake::Snake()
{
	this->type = Type::SNAKE;
	this->x = 450;
	this->y = 360;
	this->health = 0;
	for (int i = 0; i < NUM_OF_FIRE; i++)
	{
		Fire * mFire = new Fire(this->x, this->y);
		if (i <= 4)
			listFire1[i] = mFire;
		else
			listFire2[i] = mFire;
	}
	LoadResources();
}

void Snake::LoadResources()
{

	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::BOSS_TEX);

	LPANIMATION ani;
	ani = new CAnimation(100);
	file.open("Resources/Enemy/SnakeReleased.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, tex);
		ani->Add(20000 + id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//1
	file.close();//bat dau duoc tha ra

	//Tan cong
	file.open("Resources/Enemy/SnakeAttach.txt");
	file >> n;
	ani = new CAnimation(150);
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
	ani->Add(20025);
	animations->Add(300, ani);
	AddAnimation(300);//2

	//static fire
	file.open("Resources/Enemy/StaticFireSnake.txt");
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

void Snake::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->health <= 0) return;
	float tmpX, tmpY;
	Aladin *mAladin = Aladin::GetInstance();
	mAladin->GetPosition(tmpX, tmpY);
	if (this->x - tmpX > 0)//aladin o ben trai
		this->nx = -1;
	else
		this->nx = 1;
	if (animations[0]->GetCurrentFrame() == 10)
	{
		animations[0]->SetCurrentFrame();
		state = 1;
	}
	if (animations[1]->GetCurrentFrame() == 10)
	{
		Sound::GetInstance()->Play(eSound::sound_JafarSnake);
		indexFire++;
		if (indexFire <= 4)
		{
			if (listFire2[9]->GetHealth() == 0)
			{
				listUpdate2.clear();
				isFire2 = false;
				for (int i = 5; i < 10; i++)
					listFire2[i]->Revival();
			}
			isFire1 = true;
			listUpdate1.push_back(indexFire);
		}
		else
		{
			if (listFire1[4]->GetHealth() == 0)
			{
				listUpdate1.clear();
				isFire1 = false;
				for (int i = 0; i < 5; i++)
					listFire1[i]->Revival();
			}
			isFire2 = true;
			
			if (indexFire < 9) listUpdate2.push_back(indexFire);
			else if (indexFire == 9) {
				listUpdate2.push_back(9);
				indexFire = -1;
			}
		}
		animations[1]->SetCurrentFrame();
	}

	if(isFire1)
		for(auto x: listUpdate1)
			listFire1[x]->Update(dt, coObjects);
	if(isFire2)
		for (auto x : listUpdate2)
			listFire2[x]->Update(dt, coObjects);

	if (GetTickCount() - mAladin->GetUntouchableTime() >= ALADIN_BEINGHURT_TIME)
		CollisWithAladin();
	if (Aladin::GetInstance()->GetHealth() < 0) ReSetEveryThing();

}

void Snake::Render()
{
	if (this->health <= 0) return;
	int toX = 0;
	if (this->nx == 1)
		toX = -60;
	animations[state]->Render(this->x+toX, this->y, 1, this->nx, Camera::GetInstance()->GetTranform(), 1);

	for (int i = 0; i < 4; i++)
		animations[3]->Render(this->x -i*20, this->y, 1, this->nx, Camera::GetInstance()->GetTranform(), 1);

	if (isFire1)
		for (auto x : listUpdate1)
			listFire1[x]->Render();
	if(isFire2)
		for (auto x : listUpdate2)
			listFire2[x]->Render();

	if (DISPLAY_BOX == 1)
		RenderBoundingBox(-30, -43);
}

void Snake::CollisWithAladin()
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
			//mAladin->SubHealth();
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
			//	mAladin->SubHealth();
			mAladin->SetIsBeingHurt();
			mAladin->StartUntouchableTime();
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Snake::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (this->nx == -1)
	{
		left = this->x - 70;
	}
	else
		left = this->x;
	top = this->y - 35;
	right = left + 70;
	bottom = top + 82;
}	

void Snake::ReSetEveryThing()
{
	for (int i = 0; i < NUM_OF_FIRE; i++)
	{
		if (i <= 4)
			listFire1[i]->Revival();
		else
			listFire2[i]->Revival();
	}
	isFire1 = true;
	isFire2 = false;
	indexFire = -1;
	listUpdate1.clear();
	listUpdate2.clear();
}

Snake::~Snake()
{
}

