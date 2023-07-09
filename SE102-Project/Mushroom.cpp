#include "Mushroom.h"
#include "Platform.h"
#include "Coin.h"

#include "PlayScene.h"
#include "Game.h"
#include "Mario.h"


CMushroom::CMushroom(float x, float y, int Ntype) :CGameObject(x, y)
{
	this->type = Ntype;
	this->SetState(MUSHROOM_STATE_INIT);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == MUSHROOM_STATE_INIT) && (GetTickCount64() - timeAppear > MUSHROOM_TIMEOUT))
	{
		this->SetState(MUSHROOM_STATE_MOVE);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
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

void CMushroom::Render()
{
	int aniID;
	if (type == MUSHROOM_TYPE_RED)
	{
		aniID = ID_ANI_MUSHROOM_NULL_RED;
		if (state == MUSHROOM_STATE_MOVE)
		{
			aniID = ID_ANI_MUSHROOM_APPEAR_RED;
		}
	}
	else
	{
		aniID = ID_ANI_MUSHROOM_NULL_GREEN;
		if (state == MUSHROOM_STATE_MOVE)
		{
			aniID = ID_ANI_MUSHROOM_APPEAR_GREEN;
		}

	}

	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_INIT:
		timeAppear = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		ax = 0;
		break;
	case MUSHROOM_STATE_MOVE:

		vx = -MUSHROOM_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
}