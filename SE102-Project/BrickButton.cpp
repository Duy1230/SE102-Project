#include "BrickButton.h"
#include "Coin.h"


void CBrickButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(this->AniID)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BUTTON_BBOX_WIDTH / 2;
	t = y - BRICK_BUTTON_BBOX_HEIGHT / 2;
	r = l + BRICK_BUTTON_BBOX_WIDTH;
	b = t + BRICK_BUTTON_BBOX_HEIGHT;
}

void CBrickButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - timeTurnBack > TIME_TURN_BACK && AniID == ID_ANI_BRICK_BUTTON_COIN)
	{
		this->AniID = ID_ANI_BRICK_BUTTON_GLASSBRICK;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
