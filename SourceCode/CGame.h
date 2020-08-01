#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>


class CGame
{
	static CGame * _instance;
	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddev = NULL;
	LPDIRECT3DSURFACE9 backbuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

public: 

	HWND hWnd;
	void Init(HWND hWnd);

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int flipX, D3DXVECTOR2 transform, int formSize=0, int alpha=255);


	LPDIRECT3DDEVICE9 GetDirect3dDevice() { return this->d3ddev; };
	LPDIRECT3DSURFACE9 Getbackbuffer() { return this->backbuffer; };
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; };

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);

	static CGame * GetInstance();

	~CGame();
};
