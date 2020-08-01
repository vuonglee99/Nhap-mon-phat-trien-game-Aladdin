#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "define.h"

class Camera
{

	static Camera * _instance;


	D3DXVECTOR3 mPosition;
	int mWidth;
	int mHeight;
	Type mType_Map;
	float Map_End;
	int type;

public:

	Camera(int width, int height);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition();

	D3DXVECTOR2 GetTranform();

	int GetWidth();
	int GetHeight();

	RECT GetBound();
	bool isContain(RECT r1, RECT r2);

	void SetTypeMap(Type type_Map);
	static Camera * GetInstance();
	~Camera();

};
