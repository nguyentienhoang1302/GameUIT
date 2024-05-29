#include "MysteryBlock.h"

void CMBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MBLOCK_BBOX_WIDTH / 2;
	t = y - MBLOCK_BBOX_HEIGHT / 2;
	r = l + MBLOCK_BBOX_WIDTH;
	b = t + MBLOCK_BBOX_HEIGHT;
}