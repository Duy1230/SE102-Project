#include "MiniMario.h"

void CMiniMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MINIMARIO)->Render(x, y);

	//RenderBoundingBox();
}

void CMiniMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MINIMARIO_BBOX_WIDTH / 2;
	t = y - MINIMARIO_BBOX_HEIGHT / 2;
	r = l + MINIMARIO_BBOX_WIDTH;
	b = t + MINIMARIO_BBOX_HEIGHT;
}

void CMiniMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}



int CMiniMario::canMoveLeft()
{
	return route[current_node][0];
}

int CMiniMario::canMoveUp()
{
	return route[current_node][1];
}

int CMiniMario::canMoveRight()
{
	return route[current_node][2];
}

int CMiniMario::canMoveDown()
{
	return route[current_node][3];
}

bool CMiniMario::canEnter()
{
	for (int i = 0; i < sizeof(level) / sizeof(int); i++)
	{
		if (current_node == level[i])
			return 1;
	}
	return 0;
}

void CMiniMario::SetState(int state)
{
	switch (state)
	{
	case MINIMARIO_STATE_MOVE_LEFT:
		isMoving = true;
		vx = -MINIMARIO_SPEED;
		break;

	case MINIMARIO_STATE_MOVE_UP:
		isMoving = true;
		vy = -MINIMARIO_SPEED;
		break;

	case MINIMARIO_STATE_MOVE_RIGHT:
		isMoving = true;
		vx = MINIMARIO_SPEED;
		break;

	case MINIMARIO_STATE_MOVE_DOWN:
		isMoving = true;
		vy = MINIMARIO_SPEED;
		break;
	case MINIMARIO_STATE_STOP:
		isMoving = false;
		vx = 0;
		vy = 0;
	}
}

void CMiniMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<IBlock*>(e->obj))
	{
		SetState(MINIMARIO_STATE_STOP);
		this->SetPosition(e->obj->GetX(), e->obj->GetY());
	}
}