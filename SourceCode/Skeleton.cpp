#include "Skeleton.h"
#include "Aladin.h"
#include "Sound.h"

Skeleton::Skeleton(float x, float y, int direction)
{
	this->x=this->x0 = x;
	this->y =this->y0= y;
	this->nx = direction;
	this->health = 1;
	this->type = Type::SKELETON;
	state = 0;
	LoadBone();
	LoadResources();
}

void Skeleton::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::SKELETON_IMAGE);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::DIE);
	LPANIMATION ani;


	//nam yen
	ani = new CAnimation(115);
	sprites->Add(0, 0,0,120,120, tex);

	ani->Add(0);
	animations->Add(100,ani);
	AddAnimation(100);//0

	//đứng dậy
	file.open("Resources/Enemy/SkeletonStandUp.txt");
	file >> n;//18
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

	//dung yen
	ani = new CAnimation(115);

	sprites->Add(20020, 840, 120, 960, 240, tex);
	ani->Add(20020);
	animations->Add(300, ani);
	AddAnimation(300);//2

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
	animations->Add(400, ani);
	AddAnimation(400);//3
	file.close();
}

void Skeleton::LoadBone()
{
	ifstream file;
	file.open("Resources/Enemy/Bone.txt");
	int n;
	float vx, vy, state;
	file >> n;
	for (int i = 0; i < n; i++)
	{
		file >> vx >> vy >> state;
		mBone = new Bone(this->x + 25, this->y - 41, vx, vy,state);
		listBone.push_back(mBone);
	}
}

void Skeleton::Render()
{
	if (this->health > 0 )//neu k bi chem thi duoc render
		if(!isDestroy)
			animations[state]->Render(x, y, 1, this->nx, Camera::GetInstance()->GetTranform(),0 );
		else
			for (auto x : listBone)
				x->Render();
	else if(this->health<=0 && !isFinished)
		animations[state]->Render(x, y, 1, this->nx, Camera::GetInstance()->GetTranform(), 0);
	if(isDestroy)
		for (auto x : listBone)
			x->Render();
	if (DISPLAY_BOX == 1)
	{
		if(health>0)
			RenderBoundingBox(0,0);
	}
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->health <=0)
	{
		if (isBeingHurt == 1)//tu phat no hoac bi nem tao
		{
			isDestroy = true;
			for (auto x : listBone)
				x->Update(dt, coObjects);
		}
		if (!isFinished)//truong hop bi chem
		{
			state = 3;
			if (animations[3]->GetCurrentFrame() == 7)
			{
				isFinished = true;
				Aladin::GetInstance()->PlusPoint(100);
			}
		}
		else
			return;
	}
	else//binh thuong
	{
		float tmpX, tmpY;
		Aladin::GetInstance()->GetPosition(tmpX, tmpY);
		if (abs(tmpX - this->x) <= ACTIVATE_ZONE && abs(tmpY - this->y) <= ACTIVATE_ZONE_Y)
		{
			state = 1;//dung day			
			if (isReset)
			{
				isReset = false;
				animations[state]->SetCurrentFrame();
			}
			if (animations[1]->GetCurrentFrame() == 18)
			{
				state = 2;//dung yen
				dem++;
				DebugOut(L"D", NULL);
				if (dem >= 20)
				{
					Sound::GetInstance()->Play(eSound::sound_Skeleton);
					this->isDestroy = true;
					isBeingHurt = 1;
					this->health = 0;
				}
			}
		}
		else
			state = 0;
	}
}

void Skeleton::Revival()
{
	state = 0;
	isDestroy = false;
	dem = 0;
	this->health = 1;
	isReset = true;
	this->x = x0;
	this->y = y0;
	isFinished = false;
	for (int i = 0; i < listBone.size(); i++)
		listBone.at(i)->Revival();
	animations[1]->SetCurrentFrame();
	animations[3]->SetCurrentFrame();
	isBeingHurt = -1;
}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state > 0 && !isDestroy)
	{
		left = this->x - 32;
		top = this->y-20;
		right = left + 50;
		bottom = top + 70;
	}
	else
		left = top = right = bottom = 0;
}

Skeleton::~Skeleton()
{
}
