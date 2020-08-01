#include "Rope.h"




Rope::Rope(float X, float Y, int W, int H)
{
	this->x = X;
	this->y = Y;

	mWidth = W;
	mHeight = H;

	this->yStart = Y;
	this->yEnd = Y + mHeight;

	this->type = Type::ROPE;

}

void Rope::getStartEnd(float & yStart, float & yEnd)
{
	yStart = this->yStart;
	yEnd = this->yEnd;

}

void Rope::Render()
{
	if (DISPLAY_BOX == 1)
	{
		RenderBoundingBox(this->mWidth / 2, this->mHeight / 2);
	}
}

void Rope::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + mWidth;
	bottom = top + mHeight;
}

Rope::~Rope()
{
}
