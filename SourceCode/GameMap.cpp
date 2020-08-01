#include "GameMap.h"


GameMap *GameMap::_instance = NULL;


GameMap::GameMap()
{
	
}

GameMap *GameMap::GetInstance()
{
	if (_instance == NULL)
		_instance = new GameMap();
	return _instance;
}


GameMap::GameMap(Type TypeMap, LPCSTR fileMatrixPath)
{
	mSprites = CSprites::GetInstance();
	mCamera = Camera::GetInstance();
	switch (TypeMap)
	{
	case Map1:
		this->filePath = fileMatrixPath;
		mMatrix1 = new int *[Map1_Rows];
		for (int i = 0; i < Map1_Rows; i++)
			mMatrix1[i] = new int[Map1_Columns];
		break;

	case Map2:
		this->filePath = fileMatrixPath;
		mMatrix2 = new int *[Map2_Rows];
		for (int i = 0; i < Map2_Rows; i++)
			mMatrix2[i] = new int[Map2_Columns];
		break;

	case Map3:
		this->filePath = fileMatrixPath;
		mMatrix3 = new int *[Map3_Rows];
		for (int i = 0; i < Map3_Rows; i++)
			mMatrix3[i] = new int[Map3_Columns];
		break;

	case Map4:
		this->filePath = fileMatrixPath;
		mMatrix4 = new int *[Map4_Rows];
		for (int i = 0; i < Map4_Rows; i++)
			mMatrix4[i] = new int[Map4_Columns];
		break;

	case Map5:
		this->filePath = fileMatrixPath;
		mMatrix5 = new int *[Map5_Rows];
		for (int i = 0; i < Map5_Rows; i++)
			mMatrix5[i] = new int[Map5_Columns];
		break;

	case Map6:
		this->filePath = fileMatrixPath;
		mMatrix6 = new int *[Map6_Rows];
		for (int i = 0; i < Map6_Rows; i++)
			mMatrix6[i] = new int[Map6_Columns];
		break;
	case Map7:
		this->filePath = fileMatrixPath;
		mMatrix7 = new int *[Map7_Rows];
		for (int i = 0; i < Map7_Rows; i++)
			mMatrix7[i] = new int[Map7_Columns];
		break;

	case Map8:
		this->filePath = fileMatrixPath;
		mMatrix8 = new int *[Map8_Rows];
		for (int i = 0; i < Map8_Rows; i++)
			mMatrix8[i] = new int[Map8_Columns];

	case Map9:
		this->filePath = fileMatrixPath;
		mMatrix9 = new int *[Map9_Rows];
		for (int i = 0; i < Map9_Rows; i++)
			mMatrix9[i] = new int[Map9_Columns];
		break;

	case Map10:
		this->filePath = fileMatrixPath;
		mMatrix10 = new int *[Map10_Rows];
		for (int i = 0; i < Map10_Rows; i++)
			mMatrix10[i] = new int[Map10_Columns];
		break;
	case MapBoss:
		this->filePath = fileMatrixPath;
		mMatrixBoss = new int *[MapBoss_Rows];
		for (int i = 0; i < MapBoss_Rows; i++)
			mMatrixBoss[i] = new int[MapBoss_Columns];

	case MapBoss2:
		this->filePath = fileMatrixPath;
		mMatrixBoss2 = new int *[MapBoss2_Rows];
		for (int i = 0; i < MapBoss2_Rows; i++)
			mMatrixBoss2[i] = new int[MapBoss2_Columns];
	}
	
	LoadMatrix(TypeMap);
	LoadMap(TypeMap);
}

void GameMap::LoadMatrix(Type TypeMap)
{

	switch (TypeMap)
	{
	case Map1:
		this->file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix1, Map1_Rows, Map1_Columns);
		break;

	case Map2:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix2, Map2_Rows, Map2_Columns);
		break;

	case Map3:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix3, Map3_Rows, Map3_Columns);
		break;

	case Map4:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix4, Map4_Rows, Map4_Columns);
		break;
	case Map5:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix5, Map5_Rows, Map5_Columns);
		break;

	case Map6:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix6, Map6_Rows, Map6_Columns);//lay phan tu cua ma tran ra
		break;
	case Map7:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix7, Map7_Rows, Map7_Columns);//lay phan tu cua ma tran ra
		break;

	case Map8:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix8, Map8_Rows, Map8_Columns);//lay phan tu cua ma tran ra
		break;

	case Map9:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix9, Map9_Rows, Map9_Columns);//lay phan tu cua ma tran ra
		break;

	case Map10:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrix10, Map10_Rows, Map10_Columns);//lay phan tu cua ma tran ra
		break;
	case MapBoss:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrixBoss, MapBoss_Rows, MapBoss_Columns);//lay phan tu cua ma tran ra
		break;

	case MapBoss2:
		file.open(filePath);
		if (file.fail())
		{
			return;
		}
		ExportMatrix(mMatrixBoss2, MapBoss2_Rows, MapBoss2_Columns);//lay phan tu cua ma tran ra
		break;
	}

	
	
}


void GameMap::LoadMap(Type TypeMap)
{
	CTexture *texture = CTexture::GetInstance();
	LPDIRECT3DTEXTURE9 texMap = NULL;
	int Map_Tile;

	switch (TypeMap)
	{
	case Map1:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map1_Tile;
		break;

	case Map2:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map2_Tile;
		break;

	case Map3:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map3_Tile;
		break;

	case Map4:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map4_Tile;
		break;

	case Map5:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map5_Tile;
		break;

	case Map6:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map6_Tile;
		break;

	case Map7:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map7_Tile;
		break;

	case Map8:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map8_Tile;
		break;

	case Map9:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map9_Tile;
		break;

	case Map10:
		texMap = texture->Get(TypeMap);
		Map_Tile = Map10_Tile;
		break;
	case MapBoss:
		texMap = texture->Get(TypeMap);
		Map_Tile = MapBoss_Tile;
		break;

	case MapBoss2:
		texMap = texture->Get(TypeMap);
		Map_Tile = MapBoss2_Tile;
		break;

	}


	for (int i = 0; i < Map_Tile; i++)
	{
		int left = i * mTileSize;
		int right = left + mTileSize;
		int top = 0;
		int bottom = top + mTileSize;

		mSprites->Add(i + (int)TypeMap * 150, left, top, right, bottom, texMap);
	}
}


void GameMap::Draw(Type TypeMap)
{
	int Map_X, Map_Y;//khoang cach ghep giua cac map
	int rows, columns;
	switch (TypeMap)
	{
	case Map1:
		Map_X = Map1_X;
		Map_Y = Map1_Y;
		rows = Map1_Rows;
		columns = Map1_Columns;
		break;

	case Map2:
		Map_X = Map2_X;
		Map_Y = Map2_Y;
		rows = Map2_Rows;
		columns = Map2_Columns;
		break;

	case Map3:
		Map_X = Map3_X;
		Map_Y = Map3_Y;
		rows = Map3_Rows;
		columns = Map3_Columns;
		break;

	case Map4:
		Map_X = Map4_X;
		Map_Y = Map4_Y;
		rows = Map4_Rows;
		columns = Map4_Columns;
		break;

	case Map5:
		Map_X = Map5_X;
		Map_Y = Map5_Y;
		rows = Map5_Rows;
		columns = Map5_Columns;
		break;

	case Map6:
		Map_X = Map6_X;
		Map_Y = Map6_Y;
		rows = Map6_Rows;
		columns = Map6_Columns;
		break;

	case Map7:
		Map_X = Map7_X;
		Map_Y = Map7_Y;
		rows = Map7_Rows;
		columns = Map7_Columns;
		break;

	case Map8:
		Map_X = Map8_X;
		Map_Y = Map8_Y;
		rows = Map8_Rows;
		columns = Map8_Columns;
		break;

	case Map9:
		Map_X = Map9_X;
		Map_Y = Map9_Y;
		rows = Map9_Rows;
		columns = Map9_Columns;
		break;

	case Map10:
		Map_X = Map10_X;
		Map_Y = Map10_Y;
		rows = Map10_Rows;
		columns = Map10_Columns;
		break;

	case MapBoss:
		Map_X = MapBoss_X;
		Map_Y = MapBoss_Y;
		rows = MapBoss_Rows;
		columns = MapBoss_Columns;
		break;

	case MapBoss2:
		Map_X = MapBoss2_X;
		Map_Y = MapBoss2_Y;
		rows = MapBoss2_Rows;
		columns = MapBoss2_Columns;
		break;

	}


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{

			D3DXVECTOR3 position(j * mTileSize+Map_X, i * mTileSize+Map_Y, 0);
			if (mCamera != NULL)
			{
				RECT objRECT;
				objRECT.left = position.x;
				objRECT.top = position.y;
				objRECT.right = objRECT.left + mTileSize;
				objRECT.bottom = objRECT.top + mTileSize;

				if (mCamera->isContain(objRECT, mCamera->GetBound()) == false)
					continue;
			}

			DrawMiniMap(TypeMap, position.x, position.y,i,j);
		}
	}

}

void GameMap::ExportMatrix(int **matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j <columns; j++)
		{

			this->file >> matrix[i][j];

		}
	}
}

void GameMap::DrawMiniMap(Type TypeMap, float x, float y,int i,int j)
{
	switch (TypeMap)
	{
	case Map1:
		mSprites->Get(mMatrix1[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2,y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map2:
		mSprites->Get(mMatrix2[i][j] + TypeMap * 150)->Draw(x+ mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map3:
		mSprites->Get(mMatrix3[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map4:
		mSprites->Get(mMatrix4[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map5:
		mSprites->Get(mMatrix5[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map6:
		mSprites->Get(mMatrix6[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map7:
		mSprites->Get(mMatrix7[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map8:
		mSprites->Get(mMatrix8[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map9:
		mSprites->Get(mMatrix9[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case Map10:
		mSprites->Get(mMatrix10[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case MapBoss:
		mSprites->Get(mMatrixBoss[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	case MapBoss2:
		mSprites->Get(mMatrixBoss2[i][j] + TypeMap * 150)->Draw(x + mTileSize / 2, y + mTileSize / 2, 0, mCamera->GetTranform());
		break;

	}
}