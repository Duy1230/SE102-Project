#include "Fireball.h"
#include "Brick.h"
#include "Mario.h"

void CFireBall::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);

	//RenderBoundingBox();
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_BBOX_WIDTH / 2;
	t = y - FIREBALL_BBOX_HEIGHT / 2;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBrick*>(e->obj)) {
		OnCollisionWithBrick(e);
		return;
	}
	
	else if (dynamic_cast<CMario*>(e->obj)) {
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		if (!mario->GetUntouchable())
		{
			if (mario->Getlevel() == MARIO_LEVEL_FOX)
			{
				mario->SetLevel(MARIO_LEVEL_BIG);
				mario->StartUntouchable();
			}
			else if (mario->Getlevel() == MARIO_LEVEL_BIG)
			{
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->StartUntouchable();
			}
			else
			{
				mario->SetState(MARIO_STATE_DIE);
			}
		}
	}
	
}

void CFireBall::OnCollisionWithBrick(LPCOLLISIONEVENT e) {
	this->Delete();
}
