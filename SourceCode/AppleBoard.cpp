#include "AppleBoard.h"

AppleBoard * AppleBoard::_instance = NULL;

AppleBoard * AppleBoard::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new AppleBoard();
	}
	return _instance;
}

AppleBoard::AppleBoard()
{
	LoadResources();
}

AppleBoard::~AppleBoard()
{
}

void AppleBoard::Draw()
{
	CSprites *sprites = CSprites::GetInstance();
	animations[0]->Render(268, 190, 0, 1, D3DXVECTOR2(0, 0), 0);
	animations[1]->Render(16, 180, 0, 1, D3DXVECTOR2(0, 0), 0);
}

void AppleBoard::LoadResources()
{
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex= texture->Get(Type::ALADIN2);
	LPANIMATION ani;
	sprites->Add(20000, 17,3437,28,3449, tex);
	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);

	sprites->Add(20001, 13, 3568, 35, 3593, tex);
	ani = new CAnimation(100);
	ani->Add(20001);
	animations->Add(200, ani);
	AddAnimation(200);

}