#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (mario->isOnPlatform == true)
		{
			mario->SetState(MARIO_STATE_JUMP);
		}
		if (mario->isOnPlatform == true && mario->GetLevel() == MARIO_LEVEL_RACCOON && game->IsKeyDown(DIK_A) && (abs(mario->Getvx()) == MARIO_RUNNING_SPEED) && mario->isFlying == false) //(abs(mario->Getax()) == MARIO_ACCEL_RUN_X)
		{
			mario->SetState(MARIO_STATE_FLY);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_RACCOON && !mario->isOnPlatform && mario->Getvy() > 0)// && mario->isHovering == true)
		{
			mario->SetState(MARIO_STATE_HOVER);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		CGame::GetInstance()->ReloadScene();
		CGame::GetInstance()->life = 4;
		CGame::GetInstance()->coin = 0;
		break;
	case DIK_SPACE:
		if (CGame::GetInstance()->GetCurrentScene()->id == 7)
			CGame::GetInstance()->InitiateSwitchScene(8);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		mario->isFlying = false;
		mario->isHovering = false;
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}