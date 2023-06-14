#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QCOIN_STATE_INIT:
		vx = 0;
		vy = 0;
		break;
	case QCOIN_STATE_FINAL:
		//CPoint* p = new CPoint(x - 1.0f, y - 10.0f, 1000);
		goUp_begin = GetTickCount64();
		vy = -QCOIN_SPEED;
		break;
	}
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (aniID != ID_ANI_COIN_Q) return;
	if ((state == QCOIN_STATE_FINAL) && (GetTickCount64() - goUp_begin > QCOIN_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	else if ((state == QCOIN_STATE_FINAL) && (GetTickCount64() - goUp_begin > QCOIN_TIMEOUT / 1.8))
	{
		vy = QCOIN_SPEED;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}