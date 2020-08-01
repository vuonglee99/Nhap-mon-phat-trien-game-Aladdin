#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include<Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;

class MapObject
{
	int n;
	LPCSTR filePath;
	CSprites *mSprites;
	Camera *mCamera;
	unordered_map <int, D3DXVECTOR2> posObj;
	unordered_map <int, int> widthObj;
	unordered_map <int, int> heightObj;
	unordered_map <int, int> Id;


public:
	MapObject(LPCSTR filePath);
	void LoadMap();
	void Draw();
	D3DXVECTOR2 getPos(int id)
	{
		return D3DXVECTOR2(posObj[id].x, posObj[id].y);
	}

};
