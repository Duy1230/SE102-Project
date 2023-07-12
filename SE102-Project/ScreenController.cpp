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
	static int title_screen_update_timer = 0;

	int current_screen_id = CGame::GetInstance()->GetCurrentScene()->GetId();

	if (current_screen_id == TITLE_SCREEN)
	{
		CBackground* null = new CBackground(0, 0, -1);

		if (GetTickCount64() - timeLine > TIME_TITLE_SCREEN_MOVE_CURTAIN && title_screen_update_timer == 0)
		{
			null->SetState(ID_TYPE_CURTAIN_BACKGROUND, STATE_CURTAIN_MOVE);
		}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}