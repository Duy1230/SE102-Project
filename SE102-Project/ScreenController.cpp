#include "ScreenController.h"


void Controller::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_IBLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void Controller::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + 1;
	b = t + 1;
}

void Controller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	static int title_screen_timer = 0;
	int current_screen_id = CGame::GetInstance()->GetCurrentScene()->GetId();

	if (current_screen_id == TITLE_SCREEN)
	{
		static CBackground* null = new CBackground(0, 0, -1);

		if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MOVE_CURTAIN && title_screen_timer == 0)
		{
			null->SetState(ID_TYPE_CURTAIN_BACKGROUND, STATE_CURTAIN_MOVE);
			timeLine = GetTickCount64();
			title_screen_timer++;
		}
		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MOVE_TITLE && title_screen_timer == 1)
		{
			null->SetState(ID_TYPE_GAME_TITLE, STATE_TITLE_MOVE);
			null->SetState(ID_TYPE_3, STATE_THREE_MOVE);
			title_screen_timer++;
		}
		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_STOP_TITLE && title_screen_timer == 2)
		{
			null->SetState(ID_TYPE_GAME_TITLE, STATE_TITLE_STOP);
			null->SetState(ID_TYPE_3, STATE_THREE_STOP);
			title_screen_timer++;
		}
		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_TURN_BRIGHT && title_screen_timer == 3)
		{
			null->SetState(ID_TYPE_TITLE_BACKGROUND, TURN_BRIGHT);
			null->SetState(ID_TYPE_3, TURN_FLASHY);
			null->SetState(ID_TYPE_PLAYER_MODE_NULL, TURN_SINGLE_PLAYER);

			CGameObject* leaf = new CLeaf(160, 10);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(leaf, 160, 10);

			CGameObject* mushroom = new CMushroom(190, 0, MUSHROOM_TYPE_RED);
			mushroom->SetSpeed(MUSHROOM_SPEED / 8, 0);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom, 100, -100);

			CGameObject* goomba = new CGoomba(160, -500);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(goomba, 350, -480);

			CGameObject* koopas = new CKoopas(180, -500, 0, 0);
			koopas->SetState(KOOPAS_STATE_STOP);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(koopas, 120, -480);


			title_screen_timer++;
		}
		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_ADD_MARIO && title_screen_timer == 4)
		{
			CGameObject* mario = new CMario(100, 0, 2);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(mario, 100, 0);
			title_screen_timer++;
		}

		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MARIO_MOVE_RIGHT && title_screen_timer == 5)
		{
			vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->getObjects();
			for (size_t i = 1; i < objects.size(); i++)
			{
				if (dynamic_cast<CMario*>(objects[i]))
				{
					CMario* m = dynamic_cast<CMario*>(objects[i]);
					m->SetState(MARIO_STATE_WALKING_RIGHT);
					m->setnx(-1);
					title_screen_timer++;
					break;
				}
			}
		}

		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MARIO_MOVE_LEFT && title_screen_timer == 6)
		{
			vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->getObjects();
			for (size_t i = 1; i < objects.size(); i++)
			{
				if (dynamic_cast<CMario*>(objects[i]))
				{
					CMario* m = dynamic_cast<CMario*>(objects[i]);
					m->SetState(MARIO_STATE_WALKING_LEFT);
					m->setnx(-1);
					title_screen_timer++;
					break;
				}
			}
		}

		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MARIO_STOP && title_screen_timer ==7)
		{
			vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->getObjects();
			for (size_t i = 1; i < objects.size(); i++)
			{
				if (dynamic_cast<CMario*>(objects[i]))
				{
					CMario* m = dynamic_cast<CMario*>(objects[i]);
					m->SetState(MARIO_STATE_IDLE);
					m->setnx(-1);
					title_screen_timer++;
					break;
				}
			}
		}

		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MARIO_JUMP && title_screen_timer == 8)
		{
			vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->getObjects();
			for (size_t i = 1; i < objects.size(); i++)
			{
				if (dynamic_cast<CMario*>(objects[i]))
				{
					CMario* m = dynamic_cast<CMario*>(objects[i]);
					m->SetState(MARIO_STATE_JUMP);
					m->setnx(-1);
					title_screen_timer++;
					break;
				}
			}
		}

		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MARIO_FINAL && title_screen_timer == 9)
		{
			vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->getObjects();
			for (size_t i = 1; i < objects.size(); i++)
			{
				if (dynamic_cast<CMario*>(objects[i]))
				{
					CMario* m = dynamic_cast<CMario*>(objects[i]);
					m->SetState(MARIO_STATE_WALKING_RIGHT);
					m->setnx(-1);
					title_screen_timer++;
					break;
				}
			}
			}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}