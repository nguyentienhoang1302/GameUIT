#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MysteryBlock.h"
#include "Brick.h"
#include "Koopa.h"
#include "PiranhaPlant.h"
#include "Fireball.h"
#include "FirePiranhaPlant.h"
#include "Leaf.h"
#include "PlayScene.h"

#include "Collision.h"
#include "GiftSelect.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGame::GetInstance()->GetCurrentScene()->xMario = x;
	CGame::GetInstance()->GetCurrentScene()->yMario = y;
	CGame::GetInstance()->GetCurrentScene()->Mlevel = level;

	if (CGame::GetInstance()->GetCurrentScene()->id == 7)
	{
		if (this->x < 0)
			this->x = 0;
		if (this->x > 258)
			this->x = 258;
		if (this->y < 0)
			this->y = 0;
	}
	else
	{
		if (this->x < 0)
		{
			this->x = 0;
		}
		if (this->x > 2800)
		{
			this->x = 2800;
		}
		if (this->y > 194)
		{
			SetState(MARIO_STATE_DIE);
		}
		if (this->y < -230)
		{
			this->y = -230;
		}

	}



	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMBlock*>(e->obj))
		OnCollisionWithMBlock(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPPlant*>(e->obj))
		OnCollisionWithPPlant(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireball(e);
	else if (dynamic_cast<CFPlant*>(e->obj))
		OnCollisionWithFPlant(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CGSelect*>(e->obj))
		OnCollisionWithGiftSelect(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if ((e->ny < 0 && goomba->GetState() == GOOMBA_STATE_WINGED_WALK) || (e->ny < 0 && goomba->GetState() == GOOMBA_STATE_WINGED_JUMP))
	{
		goomba->SetState(GOOMBA_STATE_WALKING);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else if (e->ny < 0 && goomba->GetState() == GOOMBA_STATE_WALKING)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if ((e->ny < 0 && koopa->GetState() == KOOPA_STATE_WINGED_WALK) || (e->ny < 0 && koopa->GetState() == KOOPA_STATE_WINGED_JUMP))
	{
		koopa->SetState(KOOPA_STATE_WALK);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_WALK)
	{
		if (koopa->GetState() != KOOPA_STATE_SHELL)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (e->ny < 0 && koopa->GetState() == KOOPA_STATE_RED_WALK)
	{
		if (koopa->GetState() != KOOPA_STATE_RED_SHELL)
		{
			koopa->SetState(KOOPA_STATE_RED_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}

	else if (koopa->GetState() == KOOPA_STATE_SHELL)
	{
		if (e->ny < 0)
		{
			koopa->SetState(KOOPA_STATE_SPIN);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			return;
		}
		else if (e->nx < 0) {
			koopa->SetState(KOOPA_STATE_SPIN);
			koopa->SpinLeft();
		}
		else {
			koopa->SetState(KOOPA_STATE_SPIN);
			koopa->SpinRight();
		}
	}
	else if (koopa->GetState() == KOOPA_STATE_RED_SHELL)
	{
		if (e->ny < 0)
		{
			koopa->SetState(KOOPA_STATE_RED_SPIN);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			return;
		}
		else if (e->nx < 0) {
			koopa->SetState(KOOPA_STATE_RED_SPIN);
			koopa->SpinLeft();
		}
		else {
			koopa->SetState(KOOPA_STATE_RED_SPIN);
			koopa->SpinRight();
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CGame::GetInstance()->coin++;
}

void CMario::OnCollisionWithPPlant(LPCOLLISIONEVENT e)
{
	if (level > MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	if (level > MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::OnCollisionWithFPlant(LPCOLLISIONEVENT e)
{
	if (level > MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_SMALL || level == MARIO_LEVEL_BIG)
	{
		StartUntouchable();
		y -= 8;
		level = MARIO_LEVEL_RACCOON;
		StartUntouchable();
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = (CBrick*)(e->obj);
	if ((brick->IsBreakable() == 1 && level == MARIO_LEVEL_BIG) || (brick->IsBreakable() == 1 && level == MARIO_LEVEL_RACCOON && isFlying == false))
	{
		if (e->ny > 0)
			e->obj->Delete();
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	LPGAME game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_DOWN) || game->IsKeyDown(DIK_S))
	{
		CPortal* p = (CPortal*)e->obj;
		CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
		//this->SetPosition(p->GetxM(), p->GetyM());
	}
}

void CMario::OnCollisionWithMBlock(LPCOLLISIONEVENT e)
{
	CMBlock* mysteryblock = (CMBlock*)(e->obj);
	if (e->ny > 0 && mysteryblock->GetState() == MBLOCK_STATE_DEFAULT && isFlying == false) {
		mysteryblock->SetState(MBLOCK_STATE_EMPTY);
		if (mysteryblock->getContent() == 1)
		{
			increaseCoin();
		}
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CMushroom* mushroom = (CMushroom*)(e->obj);
	if (mushroom->GetType() == 1)
	{
		if (level == MARIO_LEVEL_SMALL || level == MARIO_LEVEL_RACCOON)
		{
			StartUntouchable();
			y -= 8;
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
	}
	else if (mushroom->GetType() == 2)
	{
		CGame::GetInstance()->life++;
	}
}

void CMario::OnCollisionWithGiftSelect(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CGSelect* gift = (CGSelect*)(e->obj);

	if (gift->GetState() == GSELECT_STATE_1)
	{
		if (level == MARIO_LEVEL_SMALL || level == MARIO_LEVEL_RACCOON)
		{
			StartUntouchable();
			y -= 8;
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
	}
	else if (gift->GetState() == GSELECT_STATE_2)
	{
		CGame::GetInstance()->life++;
	}
	else if (gift->GetState() == GSELECT_STATE_3)
	{
		if (level == MARIO_LEVEL_SMALL || level == MARIO_LEVEL_BIG)
		{
			StartUntouchable();
			y -= 8;
			level = MARIO_LEVEL_RACCOON;
			StartUntouchable();
		}
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
				{
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				}
				else
				{
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
				{
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				}
				else
				{
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
				{
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}
				else
				{
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
				{
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else
				{
					aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animation ID for Raccoon Mario
//
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		//if (abs(ax) == MARIO_ACCEL_RUN_X)
		if(isFlying)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_FLY_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_FLY_LEFT;
		}
		else
		{
			if (nx >= 0)
			{
				if (isHovering)
					aniId = ID_ANI_MARIO_RACCOON_HOVER_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			}
			else
				if (isHovering)
					aniId = ID_ANI_MARIO_RACCOON_HOVER_LEFT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
				{
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				}
				else
				{
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
				{
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				}
				else
				{
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d | Life: %d", CGame::GetInstance()->coin, CGame::GetInstance()->life);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE)
	{
		if (CGame::GetInstance()->life > 0)
		{
			CGame::GetInstance()->life--;
			CGame::GetInstance()->ReloadScene();
		}
		else
		{
			//MessageBox(NULL, TEXT("Game Over!"), TEXT("Game Over"), MB_OK | MB_ICONINFORMATION);
			return;
		}
	}

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_FLY:
		if (isSitting) break;
		isHovering = false;
		isFlying = true;
		vy = -0.2f;
		ay = 0;
		break;
	case MARIO_STATE_HOVER:
		if (isSitting) break;
		isFlying = false;
		isHovering = true;
		vy = 0.01f;
		ay = 0;
		break;
	case MARIO_STATE_RELEASE_JUMP:
		ay = MARIO_GRAVITY;
		isFlying = false;
		isHovering = false;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::increaseCoin()
{
	CGame::GetInstance()->coin++;
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

