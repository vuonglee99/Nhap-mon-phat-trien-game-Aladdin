#include "HealthBoard.h"

HealthBoard * HealthBoard::_instance = NULL;

HealthBoard * HealthBoard::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new HealthBoard();
	}
	return _instance;
}
HealthBoard::HealthBoard()
{
	LoadResources();
}

void HealthBoard::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texHealth = texture->Get(Type::ALADIN2);
	LPANIMATION ani;

	//health=0
	sprites->Add(20000, 17,3380,65,3404, texHealth);

	ani = new CAnimation(50);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);//0
	
	//health=1
	sprites->Add(20001, 17,3336, 80,3365, texHealth);
	sprites->Add(20002, 90,3336,153,3365,texHealth);
	sprites->Add(20003, 163,3336,227,3365, texHealth);
	sprites->Add(20004, 237,3335,301,3365,texHealth);

	ani = new CAnimation(50);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(200, ani);
	AddAnimation(200);//1

	//health=2
	sprites->Add(20005, 17,3289,88,3321, texHealth);
	sprites->Add(20006, 98,3289,169,3321, texHealth);
	sprites->Add(20007, 179,3289,251,3321, texHealth);
	sprites->Add(20008, 261,3289,333,3321, texHealth);

	ani = new CAnimation(50);
	ani->Add(20005);
	ani->Add(20006);
	ani->Add(20007);
	ani->Add(20008);
	animations->Add(300, ani);
	AddAnimation(300);//2

	//health=3
	sprites->Add(20009, 17,3242,97,3274, texHealth);
	sprites->Add(20010, 107,3242,187,3274, texHealth);
	sprites->Add(20011, 197,3242,276,3274, texHealth);
	sprites->Add(20012, 286, 3242,365,3274, texHealth);

	ani = new CAnimation(50);
	ani->Add(20009);
	ani->Add(20010);
	ani->Add(20011);
	ani->Add(20012);
	animations->Add(400, ani);
	AddAnimation(400);//3

	//health=4
	sprites->Add(20013, 17,3195, 105,3227,texHealth);
	sprites->Add(20014, 116,3195,204,3227, texHealth);
	sprites->Add(20015, 214, 3195,301,3227, texHealth);
	sprites->Add(20016, 311,3195,398,3227, texHealth);

	ani = new CAnimation(50);
	ani->Add(20013);
	ani->Add(20014);
	ani->Add(20015);
	ani->Add(20016);
	animations->Add(500, ani);
	AddAnimation(500);//4

	//health=5
	sprites->Add(20017, 17,3148,113,3180, texHealth);
	sprites->Add(20018, 123,3148,219,3180, texHealth);
	sprites->Add(20019, 229,3148,324,3180, texHealth);
	sprites->Add(20020, 334,3148,429,3180, texHealth);

	ani = new CAnimation(50);
	ani->Add(20017);
	ani->Add(20018);
	ani->Add(20019);
	ani->Add(20020);
	animations->Add(600, ani);
	AddAnimation(600);//5

	//health=6
	sprites->Add(20021, 17,3101,121,3133, texHealth);
	sprites->Add(20022, 131,3101,235,3133, texHealth);
	sprites->Add(20023, 245,3101,348,3133, texHealth);
	sprites->Add(20024, 358,3101,461,3133, texHealth);

	ani = new CAnimation(50);
	ani->Add(20021);
	ani->Add(20022);
	ani->Add(20023);
	ani->Add(20024);
	animations->Add(700, ani);
	AddAnimation(700);//6

	//health=7
	sprites->Add(20025, 17,3054,129,3086, texHealth);
	sprites->Add(20026, 139,3054,251,3086, texHealth);
	sprites->Add(20027, 261,3054,372,3086, texHealth);
	sprites->Add(20028, 382,3054,493,3086, texHealth);

	ani = new CAnimation(50);
	ani->Add(20025);
	ani->Add(20026);
	ani->Add(20027);
	ani->Add(20028);
	animations->Add(800, ani);
	AddAnimation(800);//7

	//health=8
	sprites->Add(20029, 17,3007,137,3039, texHealth);
	sprites->Add(20030, 147,3007,267,3039, texHealth);
	sprites->Add(20031, 277,3007,396,3039, texHealth);
	sprites->Add(20032, 406,3007,525,3039, texHealth);

	ani = new CAnimation(50);
	ani->Add(20029);
	ani->Add(20030);
	ani->Add(20031);
	ani->Add(20032);
	animations->Add(900, ani);
	AddAnimation(900);
}




HealthBoard::~HealthBoard()
{

}

void HealthBoard::Draw(int AladinHealth)
{ 
	if (AladinHealth < 0)
		AladinHealth = 0;
	int alpha = 255;
	if (AladinHealth <= 2)
		if (animations[AladinHealth]->GetCurrentFrame() % 2 == 0)
			alpha = 0;	
	animations[AladinHealth]->Render(0, 35, 0, 1, D3DXVECTOR2(0, 0), 1, alpha);
}
