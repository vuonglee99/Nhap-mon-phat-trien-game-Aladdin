#include "MapObject.h"

MapObject::MapObject(LPCSTR filePath)
{
	mCamera = Camera::GetInstance();
	mSprites = CSprites::GetInstance();
	this->filePath = filePath;
	LoadMap();
}

void MapObject::LoadMap()
{
	CTexture *texture = CTexture::GetInstance();
	LPDIRECT3DTEXTURE9 texMapObj = texture->Get(Type::Map_Object);
	int id, left, top, right, bottom, n;
	float x, y;
	ifstream file;
	file.open(filePath);
	file >> n;
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom >> x >> y;
		posObj[i] = D3DXVECTOR2(x,y);
		widthObj[i] = right - left;
		heightObj[i] = bottom - top;
		Id[i] = id;
		mSprites->Add(Type::Map_Object * 500 + id, left, top, right, bottom, texMapObj);
	}

}

void MapObject::Draw()
{
	for (int i = 0; i < posObj.size(); i++)
	{
		D3DXVECTOR2 position = getPos(i);
		if (mCamera != NULL)
		{
			RECT objRECT;
			objRECT.left = position.x;
			objRECT.top = position.y;
			objRECT.right = widthObj[i] + objRECT.left;
			objRECT.bottom = heightObj[i] + objRECT.top;
			if (mCamera->isContain(objRECT, mCamera->GetBound()) == false)
				continue;
		}
		mSprites->Get(Type::Map_Object * 500 + Id[i])->Draw(position.x+(float)(widthObj[i]/2), position.y+(float)(heightObj[i]/2), 0, mCamera->GetTranform());
	}
}
