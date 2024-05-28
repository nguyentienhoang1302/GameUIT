#include "TreeLeft.h"

void CTreeLeft::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TREELEFT)->Render(x, y);
	//RenderBoundingBox();
}

void CTreeLeft::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TREELEFT_BBOX_WIDTH / 2;
	t = y - TREELEFT_BBOX_HEIGHT / 2;
	r = l + TREELEFT_BBOX_WIDTH;
	b = t + TREELEFT_BBOX_HEIGHT;
}