#include "Brick.h"




Brick::Brick(float X, float Y, int W, int H)
{
	this->x = X;
	this->y = Y;

	mWidth = W;
	mHeight = H;

	this->type = Type::BRICK;

}

void Brick::getStartEnd(float & xStart, float & xEnd)
{
	xStart = this->x;
	xEnd = this->x + mWidth;

}

void Brick::Render()
{
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(this->mWidth / 2, this->mHeight / 2);
	}
}

void Brick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + mWidth;
	bottom = top + mHeight;
}

Brick::~Brick()
{
}
