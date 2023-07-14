#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "MiniMario.h"
#include "PlayScene.h"
#include "Background.h"

#include "AssetIDs.h"
void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	CScene* current_screen = CGame::GetInstance()->GetCurrentScene();
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (current_screen->GetId() == TITLE_SCREEN)
	{
		CBackground* b= (CBackground*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		int type = b->GetType();
		if (type != ID_TYPE_PLAYER_MODE_NULL)
		{
			switch (KeyCode)
			{
			case DIK_UP:
			{
				if (type == ID_TYPE_PLAYER_MODE_SINGLE)
					b->SetState(ID_TYPE_PLAYER_MODE_SINGLE, TURN_MULTI_PLAYER);
				else
					b->SetState(ID_TYPE_PLAYER_MODE_MULTI, TURN_SINGLE_PLAYER);
				break;
			}

			case DIK_DOWN:
			{
				if (type == ID_TYPE_PLAYER_MODE_SINGLE)
					b->SetState(ID_TYPE_PLAYER_MODE_SINGLE, TURN_MULTI_PLAYER);
				else
					b->SetState(ID_TYPE_PLAYER_MODE_MULTI, TURN_SINGLE_PLAYER);
				break;
			}

			case DIK_S:
			{
				CGame::GetInstance()->InitiateSwitchScene(MAP_SCREEN);
			}
			break;
			}
		}
	}

	if (current_screen->GetId() == MAP_SCREEN)
	{
		CMiniMario* mini = (CMiniMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mini->GetState() == MINIMARIO_STATE_STOP)
		{
			switch (KeyCode)
			{
			case DIK_LEFT:
			{
				int node_left = mini->canMoveLeft();
				if (node_left != -1 && mini->isMoving == false)
				{
					mini->SetState(MINIMARIO_STATE_MOVE_LEFT);
					mini->SetNode(node_left);
				}
				break;
			}
			
			case DIK_UP:
			{
				int node_up = mini->canMoveUp();
				if (node_up != -1 && mini->isMoving == false)
				{
					mini->SetState(MINIMARIO_STATE_MOVE_UP);
					mini->SetNode(node_up);
				}
				break;
			}

			case DIK_RIGHT:
			{
				int node_right = mini->canMoveRight();
				if (node_right != -1 && mini->isMoving == false)
				{
					mini->SetState(MINIMARIO_STATE_MOVE_RIGHT);
					mini->SetNode(node_right);
				}
				break;
			}

			case DIK_DOWN:
			{
				int node_down = mini->canMoveDown();
				if (node_down != -1 && mini->isMoving == false)
				{
					mini->SetState(MINIMARIO_STATE_MOVE_DOWN);
					mini->SetNode(node_down);
				}
				break;
			}

			case DIK_S:
			{
				if (mini->canEnter() && (mini->isMoving == false))
				{
					CGame::GetInstance()->InitiateSwitchScene(PLAY_SCREEN);
				}
				break;
			}
			}
		}
	}


	if (current_screen->GetId() == PLAY_SCREEN)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		int level = mario->Getlevel();
		int state = mario->GetState();
		if (!mario->tunneling || !mario->isWinning)
		{
			switch (KeyCode)
			{
			case DIK_DOWN:
				mario->isKeyDown = true;
				if (!mario->isHolding && !mario->tunneling && !mario->isOnPipe)
					mario->SetState(MARIO_STATE_SIT);
				break;
			case DIK_UP:
				mario->isKeyDown = true;
				break;
			case DIK_A:
				if (level == MARIO_LEVEL_FOX && state != MARIO_STATE_SIT)
					mario->setAttacking();
				break;
			case DIK_S:
			{
				if(state == MARIO_STATE_DIE)
					CGame::GetInstance()->InitiateSwitchScene(MAP_SCREEN);
				if (level == MARIO_LEVEL_FOX)
				{
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
					else if (!mario->IsOnPlatform())
					{
						mario->setSlowFalling();
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
	}
	
	
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	CScene* current_screen = CGame::GetInstance()->GetCurrentScene();
	if (current_screen->GetId() == PLAY_SCREEN)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (!mario->tunneling && !mario->isWinning)
		{
			switch (KeyCode)
			{
			case DIK_A:
				mario->isHolding = false;
			case DIK_S:
				mario->SetState(MARIO_STATE_RELEASE_JUMP);
				break;
			case DIK_DOWN:
				mario->isKeyDown = false;
				mario->SetState(MARIO_STATE_SIT_RELEASE);
			}
		}
	}
	
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CScene* current_screen = CGame::GetInstance()->GetCurrentScene();
	if (current_screen->GetId() == PLAY_SCREEN )
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		int level = mario->Getlevel();
		int state = mario->GetState();
		if (!mario->tunneling && !mario->isWinning)
		{
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
			else if (game->IsKeyDown(DIK_DOWN) || game->IsKeyDown(DIK_UP))
				mario->isKeyDown = true;
			else
			{
				mario->SetState(MARIO_STATE_IDLE);
				mario->isKeyDown = false;
			}
		}
	}
	
	
}