#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	int level = mario->Getlevel();
	int state = mario->GetState();
	switch (KeyCode)
	{
	case DIK_DOWN:
		if(!mario->isHolding)
			mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_A:
		if (level == MARIO_LEVEL_FOX && state != MARIO_STATE_SIT)
			mario->setAttacking();
		break;
	case DIK_S:
	{
		if (level == MARIO_LEVEL_FOX)
		{
			//mario->setFlying();
			if (mario->IsFlying())
			{
				mario->setFlying();
				break;
			}
			else if (abs(mario->GetVx()) == MARIO_RUNNING_SPEED && mario->IsOnPlatform())
			{
				mario->SetState(MARIO_STATE_JUMP);
				if (state != MARIO_STATE_FLYING)
					mario->SetState(MARIO_STATE_FLYING);
				break;
			}
			else
			{
				mario->SetState(MARIO_STATE_JUMP);
				break;
			}
		}
		mario->SetState(MARIO_STATE_JUMP);
		break;
	}
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_A:
		mario->isHolding = false;
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
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
	int level = mario->Getlevel();
	int state = mario->GetState();
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