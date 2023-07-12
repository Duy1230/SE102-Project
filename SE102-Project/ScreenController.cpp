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
			title_screen_timer++;
		}
		else if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_STOP_TITLE && title_screen_timer == 2)
		{
			null->SetState(ID_TYPE_GAME_TITLE, STATE_TITLE_STOP);
			title_screen_timer++;
		}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}