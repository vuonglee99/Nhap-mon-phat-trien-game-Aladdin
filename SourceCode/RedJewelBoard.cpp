#include "RedJewelBoard.h"

RedJewelBoard * RedJewelBoard::_instance = NULL;

RedJewelBoard * RedJewelBoard::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new RedJewelBoard();
	}
	return _instance;
}

RedJewelBoard::RedJewelBoard()
{
	LoadResources();
}

RedJewelBoard::~RedJewelBoard()
{
}

void RedJewelBoard::Draw()
{
	CSprites *sprites = CSprites::GetInstance();
	animations[0]->Render(220, 190,0,1, D3DXVECTOR2(0, 0), 0);
}

void RedJewelBoard::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texJewel = texture->Get(Type::ALADIN2);
	LPANIMATION ani;
	sprites->Add(20000, 49, 3435, 66, 3453, texJewel);
	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);

}