#include "IntroBackground.h"

CIntrobackground::CIntrobackground(float x, float y) : CGameObject(x, y)
{
	SetState(INTRO_BG_STATE_1);
}

void CIntrobackground::Render()
{
	int aniId = -1;
	switch (state) {
	case INTRO_BG_STATE_1:
		aniId = ID_ANI_INTRO_BACKGROUND; break;
	case INTRO_BG_STATE_2:
		aniId = ID_ANI_INTRO_BACKGROUND2; break;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CIntrobackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - INTRO_BG_BBOX_WIDTH / 2;
	t = y - INTRO_BG_BBOX_HEIGHT / 2;
	r = l + INTRO_BG_BBOX_WIDTH;
	b = t + INTRO_BG_BBOX_HEIGHT;
}

void CIntrobackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	timer += dt;
	if (timer > 6000) SetState(INTRO_BG_STATE_2);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}