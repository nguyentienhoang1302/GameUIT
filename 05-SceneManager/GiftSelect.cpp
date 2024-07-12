#include "GiftSelect.h"

CGSelect::CGSelect(float x, float y): CGameObject(x, y)
{
	SetState(GSELECT_STATE_1);
}

void CGSelect::Render()
{
	int aniId = -1;
	switch (state) {
	case GSELECT_STATE_1:
		aniId = ID_ANI_MUSHROOM_RED; break;
	case GSELECT_STATE_2:
		aniId = ID_ANI_MUSHROOM_GREEN; break;
	case GSELECT_STATE_3:
		aniId = ID_ANI_LEAF_FALLLEFT; break;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGSelect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GSELECT_BBOX_WIDTH / 2;
	t = y - GSELECT_BBOX_HEIGHT / 2;
	r = l + GSELECT_BBOX_WIDTH;
	b = t + GSELECT_BBOX_HEIGHT;
}

void CGSelect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timer += dt;
	if (timer > 200) SetState(GSELECT_STATE_2);
	if (timer > 400) SetState(GSELECT_STATE_3);
	if (timer > 600)
	{
		SetState(GSELECT_STATE_1);
		timer = 0;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}