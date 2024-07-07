#include "GreenKoopa.h"
#include "Brick.h"
#include "Goomba.h"
#include "MysteryBlock.h"

CGKoopa::CGKoopa(float x, float y, int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	walk_start = -1;
	die_start = -1;
	jumpTimer = 0;
	if (type == 1)
	{
		SetState(KOOPA_STATE_WALK);
	}
	else if (type == 2)
	{
		SetState(KOOPA_STATE_WINGED_WALK);
	}
	else if (type == 3)
	{
		SetState(KOOPA_STATE_RED_WALK);
	}
}

void CGKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_RED_SHELL || state == KOOPA_STATE_SPIN || state == KOOPA_STATE_RED_SPIN)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else if (state == KOOPA_STATE_WALK || state == KOOPA_STATE_RED_WALK)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH_WINGED / 2;
		top = y - KOOPA_BBOX_HEIGHT_WINGED / 2;
		right = left + KOOPA_BBOX_WIDTH_WINGED;
		bottom = top + KOOPA_BBOX_HEIGHT_WINGED;
	}
}

void CGKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPIN || state == KOOPA_STATE_RED_SPIN)
	{
		if (dynamic_cast<CGKoopa*>(e->obj))
			OnCollisionWithGKoopa(e);
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		if (dynamic_cast<CMBlock*>(e->obj))
			OnCollisionWithMBlock(e);
		if (dynamic_cast<CBrick*>(e->obj))
			OnCollisionWithBrick(e);
	}

	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//if ((state == KOOPA_STATE_SHELL) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	//{
	//	state = KOOPA_STATE_SPIN;
	//	return;
	//}
	//if ((state == KOOPA_STATE_RED_SHELL) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	//{
	//	state = KOOPA_STATE_RED_SPIN;
	//	return;
	//}

	if (state == KOOPA_STATE_WINGED_JUMP)
	{
		if (jumpTimer == 5)
		{
			SetState(KOOPA_STATE_WINGED_WALK);
			jumpTimer = 0;
		}
		else
		{
			SetState(KOOPA_STATE_WINGED_JUMP);
		}
	}
	if ((GetTickCount64() - walk_start > 1000) && state == KOOPA_STATE_WINGED_WALK)
	{
		SetState(KOOPA_STATE_WINGED_JUMP);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGKoopa::Render()
{
	int aniId = -1;
	if (state == KOOPA_STATE_WINGED_WALK)
	{
		aniId = ID_ANI_KOOPA_WINGED_WALK;
	}
	else if (state == KOOPA_STATE_WALK)
	{
		aniId = ID_ANI_KOOPA_WALK;
	}
	else if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SPIN)
	{
		aniId = ID_ANI_KOOPA_SPIN;
	}
	else if (state == KOOPA_STATE_WINGED_JUMP)
	{
		aniId = ID_ANI_KOOPA_WINGED_JUMP;
	}
	else if (state == KOOPA_STATE_RED_WALK)
	{
		aniId = ID_ANI_KOOPA_RED_WALK;
	}
	else if (state == KOOPA_STATE_RED_SPIN)
	{
		aniId = ID_ANI_KOOPA_RED_SPIN;
	}
	else if (state == KOOPA_STATE_RED_SHELL)
	{
		aniId = ID_ANI_KOOPA_RED_SHELL;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALK:
		vx = -KOOPA_WALKING_SPEED;
		//vx = 0;
		break;
	case KOOPA_STATE_WINGED_WALK:
		//vx = 0;
		walk_start = GetTickCount64();
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WINGED_JUMP:
		jumpTimer++;
		if (jumpTimer == 5)
		{
			vy = -KOOPA_VY_JUMP_MAX;
		}
		else
		{
			vy = -KOOPA_VY_JUMP;
		}
		break;
	case KOOPA_STATE_RED_SHELL:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_RED_WALK:
		vx = -KOOPA_WALKING_SPEED;
		//vx = 0;
		break;
	case KOOPA_STATE_SPIN:
		vx = KOOPA_SPINNING_SPEED;
		//vx = 0;
		break;
	case KOOPA_STATE_RED_SPIN:
		vx = KOOPA_SPINNING_SPEED;
		//vx = 0;
		break;
	}
	CGameObject::SetState(state);
}

void CGKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() == GOOMBA_STATE_WINGED_WALK || goomba->GetState() == GOOMBA_STATE_WINGED_JUMP)
	{
		goomba->SetState(GOOMBA_STATE_WALKING);
	}
	else if (goomba->GetState() == GOOMBA_STATE_WALKING)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
		}
	}
}

void CGKoopa::OnCollisionWithGKoopa(LPCOLLISIONEVENT e)
{
	CGKoopa* koopa = dynamic_cast<CGKoopa*>(e->obj);

	if (koopa->GetState() == KOOPA_STATE_WINGED_WALK || koopa->GetState() == KOOPA_STATE_WINGED_JUMP)
	{
		koopa->SetState(KOOPA_STATE_WALK);
	}
	else if (koopa->GetState() == KOOPA_STATE_WALK)
	{
		if (koopa->GetState() != KOOPA_STATE_SHELL)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
		}
	}
	else if (koopa->GetState() == KOOPA_STATE_RED_WALK)
	{
		if (koopa->GetState() != KOOPA_STATE_RED_SHELL)
		{
			koopa->SetState(KOOPA_STATE_RED_SHELL);
		}
	}
}


void CGKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = (CBrick*)(e->obj);
	if (brick->IsBreakable() == 1)
	{
		e->obj->Delete();
	}
}

void CGKoopa::OnCollisionWithMBlock(LPCOLLISIONEVENT e)
{
	CMBlock* mysteryblock = (CMBlock*)(e->obj);
	if (e->ny > 0 && mysteryblock->GetState() == MBLOCK_STATE_DEFAULT) {
		mysteryblock->SetState(MBLOCK_STATE_EMPTY);
	}
}

void CGKoopa::SpinLeft() {
	//this->SetState(KOOPA_STATE_SPIN);
	vx = KOOPA_SPINNING_SPEED;
}

void CGKoopa::SpinRight() {
	//this->SetState(KOOPA_STATE_SPIN);
	vx = -KOOPA_SPINNING_SPEED;
}