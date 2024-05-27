#include "Ground1.h"

void CGround1::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GROUND1)->Render(x, y);
	//RenderBoundingBox();
}

void CGround1::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GROUND1_BBOX_WIDTH / 2;
	t = y - GROUND1_BBOX_HEIGHT / 2;
	r = l + GROUND1_BBOX_WIDTH;
	b = t + GROUND1_BBOX_HEIGHT;
}