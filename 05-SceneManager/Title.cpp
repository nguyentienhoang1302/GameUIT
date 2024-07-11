#include "Title.h"

void CTitle::Render()
{
	int aniId = ID_ANI_TITLE;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CTitle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TITLE_BBOX_WIDTH / 2;
	t = y - TITLE_BBOX_HEIGHT / 2;
	r = l + TITLE_BBOX_WIDTH;
	b = t + TITLE_BBOX_HEIGHT;
}

void CTitle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted) {
		if ((GetTickCount64() - appear) > 3000)
		{
			if (y < 90)
			{
				vy = 0.2f;
				y += vy * dt;
			}
			else
				vy = 0;
		}
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