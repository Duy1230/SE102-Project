#include "IBlock.h"


void IBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_IBLOCK)->Render(x, y);
	RenderBoundingBox();
}

void IBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - IBLOCK_BBOX_WIDTH / 2;
	t = y - IBLOCK_BBOX_HEIGHT / 2;
	r = l + IBLOCK_BBOX_WIDTH;
	b = t + IBLOCK_BBOX_HEIGHT;
}