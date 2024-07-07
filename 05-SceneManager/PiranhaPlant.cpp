#include "PiranhaPlant.h"
#include "debug.h"

void CPPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
}

void CPPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	risetime += dt;
	if (risetime < 1500) {
		Rise();
	}
	else if (risetime < 4000) {
		Fall();
	}
	else risetime = 0;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPPlant::Render()
{
	if (!settime) {
		y0 = y;
		risetime = 0;
		settime = true;
	}
	CAnimations::GetInstance()->Get(ID_ANI_PIRANHAPLANT)->Render(x, y);

	//RenderBoundingBox();
}

void CPPlant::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPPlant::Rise() {
	if (y < y0 - PIRANHAPLANT_BBOX_HEIGHT) {
		y = y0 - PIRANHAPLANT_BBOX_HEIGHT;
		vy = 0;
	}
	else
		vy = -0.022f;
}
void CPPlant::Fall() {
	if (y > y0 + 6)
	{
		vy = 0;
		y = y0 + 6;
	}
	else
		vy = 0.022f;
}

