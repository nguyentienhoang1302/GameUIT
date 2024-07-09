#include "PiranhaPlant.h"

CPPlant::CPPlant(float x, float y) :CGameObject(x, y)
{
	y0 = y + 6;
	risetime = 0;
}

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
	if (risetime < 4000) {
		Rise();
	}
	else if (risetime < 8000) {
		Fall();
	}
	else risetime = 0;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPPlant::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_PIRANHAPLANT)->Render(x, y);
}

void CPPlant::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPPlant::Rise() 
{
	if (y < y0 - PIRANHAPLANT_BBOX_HEIGHT) 
	{
		y = y0 - PIRANHAPLANT_BBOX_HEIGHT;
		vy = 0;
	}
	else
		vy = -0.02f;
}
void CPPlant::Fall() 
{
	if (y > y0 + 5)
	{
		vy = 0;
		y = y0 + 5;
	}
	else
		vy = 0.02f;
}

