#pragma once
#include "GameObject.h"
#include <fstream>
#include"define.h"
#include"Brick.h"
#include "Camera.h"
#include"Arrow.h"
#include "Bob.h"
#include "MovingBrick.h"
#include"Wall.h"
#include "Rope.h"
#include "AppleItem.h"
#include "RedJewel.h"
#include "Genie.h"
#include "Heart.h"
#include "RestartPoint.h"
#include "Bat.h"
#include "Guard.h"
#include "Skeleton.h"
#include "Monkey.h"
#include<iostream>

using namespace std;

#define GRID_CELL_HEIGHT 1120
#define GRID_CELL_WIDTH 284

#define MAX_GRID_ROW 2
#define MAX_GRID_COLUMN 8

//chia map thanh cac cell
//moi cell chua 1 ds cac obj thuoc cell do
//camera thuoc cell nao thi lay obj thuoc cell do ra
class Grid
{
	LPCSTR gridPath;//duong dan chua file cac obj
	vector<GameObject*> cells[MAX_GRID_ROW][MAX_GRID_COLUMN];//vector hai chieu 
	static Grid *_instance;
	bool isResetMV = true, isResetBob = true;

public:
	Grid();
	void Clear();
	void SetGridPath(LPCSTR gridPath);
	void LoadGrid();
	void LoadObjectIntoGrid(int id, int type, int direction, int width, int height, float x, float y,int state);
	GameObject *NewObject(int id, int type, int direction, int width, int height, float x, float y,int state);
	void ReadMatrixGrid(int row, int column,vector<int> &);
	void FindObjInMatrix(int &, int &);
	void Revival(vector<GameObject *> listObj);
	void ListObject(vector<GameObject *> &listObj);//tra ve list object dang thuoc trong camera
	static Grid *GetInstance();
	~Grid();


};