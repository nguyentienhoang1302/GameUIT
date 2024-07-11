#include "Curtain.h"

void CCurtain::Render()
{
	int aniId = ID_ANI_CURTAIN;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CCurtain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CURTAIN_BBOX_WIDTH / 2;
	t = y - CURTAIN_BBOX_HEIGHT / 2;
	r = l + CURTAIN_BBOX_WIDTH;
	b = t + CURTAIN_BBOX_HEIGHT;
}

void CCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted) {
		if (y > -112)
		{
			vy = -0.2f; 
			y += vy * dt;
		}
		else
			vy = 0;
		if ((GetTickCount64() - appear) > 6000)
		{
			y = 0;
			isDeleted = true;
			return;
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}