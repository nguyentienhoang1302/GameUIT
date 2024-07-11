#include "StageSelect.h"

void CSSelect::Render()
{
	int aniId = ID_ANI_STAGE_SELECT;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CSSelect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - STAGE_SELECT_BBOX_WIDTH / 2;
	t = y - STAGE_SELECT_BBOX_HEIGHT / 2;
	r = l + STAGE_SELECT_BBOX_WIDTH;
	b = t + STAGE_SELECT_BBOX_HEIGHT;
}