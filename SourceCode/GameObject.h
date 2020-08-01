#pragma once
#include<d3dx9.h>
#include<d3d9.h>
#include"CGame.h"
#include"Sprite.h"
#include "Texture.h"
#include<vector>
#include "define.h"
#include <iostream>
#include<fstream>
#include <Windows.h>
#include <algorithm>
#include "Camera.h"
#include "debug.h"

using namespace std;


#define DISPLAY_BOX 0

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject
{

protected:
	int health;
	Type type;
	int id;

	float x, y;

	float vx, vy;

	float nx, ny;

	float dx, dy;

	DWORD dt;
	int currentState;
	bool isCollisWithWeapon;
	int isBeingHurt= - 1;
	vector<LPANIMATION> animations;

public:

	GameObject();
	void SetState(int state) { this->currentState = state; }
	void AddAnimation(int aniId);


	Type GetType();

	int GetID();
	void SetID(int id);

	void SetDirection(int Direction);
	int GetDirection();


	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	float GetPosY() { return this->y; }
	float GetPosX() { return this->x; }

	void SetSpeed(float vx, float vy);
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	
	void RenderBoundingBox(int, int);

	int GetHealth() { return this->health; }
	virtual void SubHealth() { this->health--; }
	void SubHealth(int x) { this->health = this->health - x; }
	void SetFinish() { }
	void Healing(int x) { this->health += x; }
	void SetHealth(int x) { this->health = x; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	bool AABBcollision(LPGAMEOBJECT gameobj);
	bool GetIsCollisWithWeapon()
	{
		return this->isCollisWithWeapon;
	}

	void SetIsBeingHurt(int isHurt)
	{
		this->isBeingHurt = isHurt;
	}

	int GetIsBeingHurt()
	{
		return this->isBeingHurt;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual int GetState() { return currentState; };
	virtual float GetVx() { return vx; }
	virtual void LoadAni();
	virtual void Reset();
	virtual void Revival();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	
	~GameObject();
};

