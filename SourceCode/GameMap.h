#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include<Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include <iostream>
#include <fstream>
#include "Camera.h"

using namespace std;

class GameMap
{
	static GameMap *_instance;
	int **mMatrix1, **mMatrix2, **mMatrix3, **mMatrix4, **mMatrix5;
	int **mMatrix6, **mMatrix7, **mMatrix8, **mMatrix9, **mMatrix10, **mMatrixBoss, **mMatrixBoss2;
	int mColumns, mRows;
	int mTileSize = 32;
	LPCSTR filePath;
	D3DXIMAGE_INFO MapInfo;
	CSprites *mSprites;
	Camera *mCamera;
	ifstream file;
public:
	GameMap();
	GameMap(Type TypeMap, LPCSTR fileMatrixPath);
	void LoadMatrix(Type TypeMap);
	void LoadMap(Type TypeMap);
	void Draw(Type TypeMap);
	void ExportMatrix(int **, int, int);

	void DrawMiniMap(Type TypeMap, float x, float y,int i,int j);
	static GameMap *GetInstance();
	~GameMap();
};
