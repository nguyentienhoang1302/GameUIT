#include "FirePiranhaPlant.h"
#include "Fireball.h"

CFPlant::CFPlant(float x, float y, int type) :CGameObject(x, y)
{
	this->type = type;
	//SetState(FIREPIRANHAPLANT_STATE_TL);
	SetState(FIREPIRANHAPLANT_STATE_WAIT);
}

void CFPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type == 1)
	{
		left = x - FIREPIRANHAPLANT_BBOX_WIDTH / 2;
		top = y - FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN / 2;
		right = left + FIREPIRANHAPLANT_BBOX_WIDTH;
		bottom = top + FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN;
	}
	else if (type == 2)
	{
		left = x - FIREPIRANHAPLANT_BBOX_WIDTH / 2;
		top = y - FIREPIRANHAPLANT_BBOX_HEIGHT_RED / 2;
		right = left + FIREPIRANHAPLANT_BBOX_WIDTH;
		bottom = top + FIREPIRANHAPLANT_BBOX_HEIGHT_RED;
	}
}

void CFPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	if (state == FIREPIRANHAPLANT_STATE_WAIT && CGame::GetInstance()->GetCurrentScene()->xMario + 180 >= this->x)
	{
		SetState(FIREPIRANHAPLANT_STATE_TL);
		isStart = true;
	}

	if (isStart == true)
	{
		x += vx * dt;
		y += vy * dt;
		risetime += dt;
		if (risetime < 2000) {
			Rise();
		}
		else if (risetime < 5000) {
			Shoot();
		}
		else if (risetime < 8000) {
			isShooting = false;
			Fall();
		}
		else risetime = 0;

		float x1 = CGame::GetInstance()->GetCurrentScene()->xMario;
		float y1 = CGame::GetInstance()->GetCurrentScene()->yMario;
		if (x1 < x && y1 < y) {
			SetState(FIREPIRANHAPLANT_STATE_TL);
		}
		else if (x1 < x && y1 > y) {
			SetState(FIREPIRANHAPLANT_STATE_BL);
		}
		else if (x1 > x && y1 < y) {
			SetState(FIREPIRANHAPLANT_STATE_TR);
		}
		else if (x1 > x && y1 > 1) {
			SetState(FIREPIRANHAPLANT_STATE_BR);
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void CFPlant ::Render()
{
	int aniId = -1;
	if (state == FIREPIRANHAPLANT_STATE_BL && type == 1 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_BL_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BL && type == 1 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_BL_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TL && type == 1 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_TL_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TL && type == 1 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_TL_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TR && type == 1 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_TR_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TR && type == 1 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_TR_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BR && type == 1 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_BR_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BR && type == 1 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_GREEN_BR_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BL && type == 2 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_BL_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BL && type == 2 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_BL_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TL && type == 2 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_TL_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TL && type == 2 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_TL_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TR && type == 2 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_TR_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_TR && type == 2 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_TR_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BR && type == 2 && isShooting == true)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_BR_SHOOT;
	}
	else if (state == FIREPIRANHAPLANT_STATE_BR && type == 2 && isShooting == false)
	{
		aniId = ID_ANI_PIRANHAPLANT_RED_BR_IDLE;
	}
	else if (state == FIREPIRANHAPLANT_STATE_WAIT)
	{
		aniId = ID_ANI_PIRANHAPLANT_WAIT;
	}
	
	if (!settime) 
	{
		if (type == 1)
		{
			y0 = y + 6;
			risetime = 0;
			settime = true;
		}
		else if (type == 2)
		{
			y0 = y + 10;
			risetime = 0;
			settime = true;
		}
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}


void CFPlant::SetState(int state)
{
	CGameObject::SetState(state);
}

void CFPlant::Rise() 
{
	if (type == 1)
	{
		if (y < y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN)
		{
			y = y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN;
			vy = 0;
		}
		else
			vy = -0.02f;
	}
	else if (type == 2)
	{
		if (y < y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_RED)
		{
			y = y0 - FIREPIRANHAPLANT_BBOX_HEIGHT_RED;
			vy = 0;
		}
		else
			vy = -0.02f;
	}
}

void CFPlant::Fall() 
{
	if (y > y0 + 5)
	{
		vy = 0;
		y = y0 + 5;
	}
	else
		vy = 0.02f;
}

void CFPlant::Shoot() 
{
	if (isShooting == false)
	{
		switch (state) {
		case FIREPIRANHAPLANT_STATE_TL:
			subObject = new CFireball(x, y, 1);
			subObject->SetPosition(x, y - 9);
			break;
		case FIREPIRANHAPLANT_STATE_BL:
			subObject = new CFireball(x, y, 2);
			subObject->SetPosition(x, y - 9);
			break;
		case FIREPIRANHAPLANT_STATE_TR:
			subObject = new CFireball(x, y, 3);
			subObject->SetPosition(x, y - 9);
			break;
		case FIREPIRANHAPLANT_STATE_BR:
			subObject = new CFireball(x, y, 4);
			subObject->SetPosition(x, y - 9);
			break;
		}
		isShooting = true;
		CreateSubObject = true;
	}
	vy = 0;
}