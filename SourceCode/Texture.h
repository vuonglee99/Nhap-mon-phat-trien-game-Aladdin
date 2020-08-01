#pragma once
#include<unordered_map>
#include<d3dx9.h>
#include<d3d9.h>
#include"CGame.h"
#include<Windows.h>
#include "define.h"

using namespace std;

#define DEFAULT_TRANS_COLOR D3DCOLOR_XRGB(255, 163, 177)
class CTexture
{
	static CTexture * _instance;
	unordered_map <Type, LPDIRECT3DTEXTURE9> texture;
	
	unordered_map <Type, D3DXIMAGE_INFO  > image_info;

public:
	CTexture();
	void Add(Type id, LPCSTR texturePath, D3DCOLOR transparentColor = DEFAULT_TRANS_COLOR);
	void LoadTexTure();

	LPDIRECT3DTEXTURE9 Get(Type id);
	D3DXIMAGE_INFO GetImageInfo(Type id);
	static CTexture* GetInstance();

	~CTexture();
};


