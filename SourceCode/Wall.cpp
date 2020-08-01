#include "Wall.h"




Wall::Wall(float X, float Y, int W, int H)
{
	this->x = X;
	this->y = Y;

	mWidth = W;
	mHeight = H;

	this->type = Type::WALL;

}

void Wall::getStartEnd(float & xStart, float & xEnd)
{
	xStart = this->x;
	xEnd = this->x + mWidth;

}

void Wall::Render()
{
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(this->mWidth / 2, this->mHeight / 2);
	}
}

void Wall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + mWidth;
	bottom = top + mHeight;
}

Wall::~Wall()
{
}
