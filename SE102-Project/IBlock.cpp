#include "IBlock.h"


void IBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_IBLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void IBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t + height;
}