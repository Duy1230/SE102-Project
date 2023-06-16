#include "FGoomba.h"
#include "Platform.h"
#include "Coin.h"
#include "IBlock.h"

#include "PlayScene.h"
#include "Game.h"



FGoomba::FGoomba(float x, float y) :CGameObject(x, y)
{
	isOnPlatform = false;
	vx = -FGOOMBA_WALKING_SPEED;
	this->ax = 0;
	this->ay = FGOOMBA_GRAVITY;
	die_start = -1;
	SetState(FGOOMBA_STATE_WALKING_WITH_WING);
}

void FGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FGOOMBA_STATE_DIE)
	{
		left = x - FGOOMBA_BBOX_WIDTH / 2;
		top = y - FGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FGOOMBA_BBOX_WIDTH;
		bottom = top + FGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - FGOOMBA_BBOX_WIDTH / 2;
		top = y - FGOOMBA_BBOX_HEIGHT / 2;
		right = left + FGOOMBA_BBOX_WIDTH;
		bottom = top + FGOOMBA_BBOX_HEIGHT;
	}
}

void FGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void FGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (dynamic_cast<IBlock*>(e->obj))
	{
		IBlock* p = dynamic_cast<IBlock*>(e->obj);
		if (p->type != 11 && p->type != -1)
			return;
		if (e->ny != 0)
		{
			isOnPlatform = true;
			vx = -vx;
			if (state == FGOOMBA_STATE_FLYING && jumpStep == FGOOMBA_JUMPSTEP)
			{
				vy = -3 * FGOOMBA_JUMP_SPEED;
				jumpStep += 1;
				isOnPlatform = false;
			}
			else if (state == FGOOMBA_STATE_FLYING)
			{
				vy = -FGOOMBA_JUMP_SPEED;
				jumpStep += 1;
				isOnPlatform = false;
			}
			else
			{
				vy = 0;
			}
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
		//return;
	}
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		isOnPlatform = true;
		if (state == FGOOMBA_STATE_FLYING && jumpStep == FGOOMBA_JUMPSTEP)
		{
			vy = -3 * FGOOMBA_JUMP_SPEED;
			jumpStep += 1;
			isOnPlatform = false;
		}
		else if (state == FGOOMBA_STATE_FLYING)
		{
			vy = -FGOOMBA_JUMP_SPEED;
			jumpStep += 1;
			isOnPlatform = false;
		}
		else
		{
			vy = 0;
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void FGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == FGOOMBA_STATE_WALKING_WITH_WING && (GetTickCount64() - stateChangeTime > FGOOMBA_STATE_TIMEOUT))
	{
		this->SetState(FGOOMBA_STATE_FLYING);
	}
	else if (state == FGOOMBA_STATE_FLYING && jumpStep == FGOOMBA_JUMPSTEP + 1)
	{
		this->SetState(FGOOMBA_STATE_WALKING_WITH_WING);
	}
	else if ((state == FGOOMBA_STATE_DIE ) && (GetTickCount64() - die_start > FGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	else if ((state == FGOOMBA_STATE_DIE_KOOPAS) && (GetTickCount64() - die_start > FGOOMBA_DIE_TIMEOUT_KOOPAS))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FGoomba::Render()
{
	int aniID;
	if (state == FGOOMBA_STATE_DIE)
	{
		aniID = ID_ANI_FGOOMBA_DIE;
	}
	else if (state == FGOOMBA_STATE_WALKING_WITH_WING)
		aniID = ID_ANI_FGOOMBA_WALKING_WITH_WING;
	else if (state == FGOOMBA_STATE_WALKING || state == FGOOMBA_STATE_DIE_KOOPAS)
		aniID = ID_ANI_FGOOMBA_WALKING;
	else if (state == FGOOMBA_STATE_FLYING && jumpStep > 5)
		aniID = ID_ANI_FGOOMBA_FLY;
	else
		aniID = ID_ANI_FGOOMBA_PREPARE_FLYING;

	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void FGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FGOOMBA_STATE_WALKING_WITH_WING:
		stateChangeTime = GetTickCount64();
		jumpStep = 0;
		isOnPlatform = true;
		//vx = -FGOOMBA_WALKING_SPEED;
		break;
	case FGOOMBA_STATE_FLYING:
		vy = -FGOOMBA_WALKING_SPEED;
		isOnPlatform = false;
		break;
	case FGOOMBA_STATE_DIE_KOOPAS:
		die_start = GetTickCount64();
		vy = -0.2f;
		break;
	case FGOOMBA_STATE_WALKING:
		break;
	case FGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}