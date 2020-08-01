#include "Sprite.h"
#include"CGame.h"



CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

}

void CSprite::Draw(float x, float y, int isLeft, D3DXVECTOR2 transform, int formSize, int alpha)
{
	CGame *game = CGame::GetInstance();
	int l = this->left;
	game->Draw(x, y, this->texture, left,top,right,bottom, isLeft, transform,formSize, alpha);

}
CSprites * CSprites::_instance = NULL;



void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;

}

LPSPRITE CSprites::Get(int id)
{

	return sprites[id];
}

CSprites *CSprites::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CSprites();

	}
	return _instance;
}

CAnimation::CAnimation(int defaultTime)
{
	this->defaultTime = defaultTime;
	this->lastFrameTime -= 1;
	this->currentFrame -= 1;
}

void CAnimation::Add(int spriteId, DWORD Time)
{
	int t = Time;
	if (Time == 0)
	{
		t = this->defaultTime;
	}
	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPCANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

int CAnimation::Render(float x, float y, int isAttach, int isLeft, D3DXVECTOR2 trans,int formSize, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
			{
				if (isAttach == 0)//0 la khong loop
				{
					frames[0]->GetSprite()->Draw(x, y, isLeft, trans,formSize, alpha);// Tranh tinh trang nhay o frame cuoi
					currentFrame = -1;
					return -1;
				}
				currentFrame = 0;
			}
		}
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, isLeft, trans, formSize, alpha);

}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{

	return animations[id];
}
CAnimations * CAnimations::_instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CAnimations();
	}
	return _instance;
}
