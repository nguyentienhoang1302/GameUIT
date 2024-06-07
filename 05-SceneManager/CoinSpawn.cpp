#include "CoinSpawn.h"

void CCoinSpawn::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COINFROMBOX)->Render(x, y - 16);
	if (!setAppear) {
		appear = GetTickCount64();
		setAppear = true;
	}
	//RenderBoundingBox();
}

void CCoinSpawn::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COINFROMBOX_BBOX_WIDTH / 2;
	t = y - COINFROMBOX_BBOX_HEIGHT / 2;
	r = l + COINFROMBOX_BBOX_WIDTH;
	b = t + COINFROMBOX_BBOX_HEIGHT;
}


void CCoinSpawn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted) {
		vy = -0.32f; y += vy * dt;
		if ((GetTickCount64() - appear) > 200)
		{
			y = 0;
			isDeleted = true;
			return;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}