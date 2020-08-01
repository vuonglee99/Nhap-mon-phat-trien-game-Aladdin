#include "Arrow.h"

Arrow::Arrow(float x, float y, int width, int height,int state)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	mState = state;
	this->type = Type::ARROW;
	LoadResources();
}

void Arrow::LoadResources()
{
	ifstream file;
	int id, left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texArrow = texture->Get(Type::Map_Object);
	
	LPANIMATION ani;
	

	//di ra ngoai
	file.open("Resources/Object/Arrow.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(id, left, top, right, bottom, texArrow);
		ani->Add(id);

	}
	animations->Add(100, ani);
	AddAnimation(100);//0
	file.close();

	//dung yen ben ngoai
	sprites->Add(10006, 1344, 380, 1393, 415, texArrow);
	ani = new CAnimation(120);
	ani->Add(10006);
	animations->Add(200, ani);
	AddAnimation(200);//1

	//di vao trong
	file.open("Resources/Object/Arrow2.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(id, left, top, right, bottom, texArrow);
		ani->Add(id);

	}
	animations->Add(300, ani);
	AddAnimation(300);//2
	file.close();

	//dung yen ben trong
	sprites->Add(10013, 982, 381, 1031, 416, texArrow);
	ani = new CAnimation(120);
	ani->Add(10013);
	animations->Add(400, ani);
	AddAnimation(400);//3
}

void Arrow::Render()
{
	int ani_ID = mState;
	int loop = 1;
	
	animations[ani_ID]->Render(this->x + 24.5, this->y + 17.5, loop, this->nx, Camera::GetInstance()->GetTranform());

	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(this->width / 4, this->height / 8);
	}
}

void Arrow::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	switch (mState)
	{
	case 0://di ra
		if (animations[0]->GetCurrentFrame() == 5)
		{
			dem = 0;
			mState = 1;
		}
		break;
	case 1://dung yen ben ngoai
		dem++;
		if (dem>=20)
		{
			mState = 2;
			animations[2]->SetCurrentFrame();
		}
		break;
	case 2://di vao
		if (animations[2]->GetCurrentFrame() == 5)
		{
			dem = 0;
			mState = 3;
		}
		break;
	case 3://dung yen ben trong
		dem++;
		if (dem>=100)
		{
			mState = 0;
			animations[0]->SetCurrentFrame();
		}
		break;
	}
}

void Arrow::StartCountingTime(DWORD & t)
{
	t = GetTickCount();
}

void Arrow::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (mState==1)
	{
		left = x;
		top = y;
		right = left + width/2;
		bottom = top + height/4;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}
Arrow::~Arrow()
{

}
