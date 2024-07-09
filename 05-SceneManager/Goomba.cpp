#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->type = type;
	SetState(GOOMBA_STATE_WAITING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == GOOMBA_STATE_WALKING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH_WINGED/2;
		top = y - GOOMBA_BBOX_HEIGHT_WINGED/2;
		right = left + GOOMBA_BBOX_WIDTH_WINGED;
		bottom = top + GOOMBA_BBOX_HEIGHT_WINGED;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	if (state == GOOMBA_STATE_WINGED_JUMP)
	{
		jumpTimer++;
		if (jumpTimer == 5)
		{
			SetState(GOOMBA_STATE_WINGED_WALK);
			jumpTimer = 0;
		}
		else
		{
			SetState(GOOMBA_STATE_WINGED_JUMP);
		}
	}
	if ((GetTickCount64() - walk_start > 1000) && state == GOOMBA_STATE_WINGED_WALK)
	{
		SetState(GOOMBA_STATE_WINGED_JUMP);
	}
	if (state == GOOMBA_STATE_WAITING && CGame::GetInstance()->GetCurrentScene()->xMario + 180 >= this->x)
	{
		this->ax = 0;
		this->ay = GOOMBA_GRAVITY;
		walk_start = -1;
		die_start = -1;
		jumpTimer = 0;
		if (type == 1)
		{
			SetState(GOOMBA_STATE_WALKING);
		}
		else if (type == 2)
		{
			SetState(GOOMBA_STATE_WINGED_WALK);
		}
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;
	if (state == GOOMBA_STATE_WINGED_WALK)
	{
		aniId = ID_ANI_GOOMBA_WINGED_WALK;
	}
	else if (state == GOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_GOOMBA_WALKING;
	}
	else if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_WINGED_JUMP)
	{
		aniId = ID_ANI_GOOMBA_WINGED_JUMP;
	}
	else if (state == GOOMBA_STATE_WAITING)
	{
		aniId = ID_ANI_GOOMBA_WAITING;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_WINGED_WALK:
			walk_start = GetTickCount64();
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_WINGED_JUMP:
			vy = -GOOMBA_VY_JUMP;
			break;
		case GOOMBA_STATE_WAITING:
			vx = 0;
			vy = 0;
			ay = 0;
			break;
	}
	CGameObject::SetState(state);
}
