#include "Leaf.h"

#include "PlayScene.h"
#include "Game.h"


CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->SetState(LEAF_STATE_MOVEUP);
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}


void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	x += vx * dt;
	y += vy * dt;

	if ((state == LEAF_STATE_MOVEUP) && (GetTickCount64() - timeMoveup > LEAF_TIME_MOVEUP))
	{
		this->SetState(LEAF_STATE_FALL_RIGHT);
	}
	else if ((state == LEAF_STATE_FALL_RIGHT) && (GetTickCount64() - timeTurn > LEAF_TIME_TURN))
		this->SetState(LEAF_STATE_FALL_LEFT);
	else if ((state == LEAF_STATE_FALL_LEFT) && (GetTickCount64() - timeTurn > LEAF_TIME_TURN))
		this->SetState(LEAF_STATE_FALL_RIGHT);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_FALL_RIGHT;
	if (state == LEAF_STATE_FALL_LEFT)
	{
		aniId = ID_ANI_LEAF_FALL_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_MOVEUP:
		timeMoveup = GetTickCount64();
		vx = 0;
		vy = -LEAF_SPEED_MOVEUP;
		break;
	case LEAF_STATE_FALL_RIGHT:
		timeTurn = GetTickCount64();
		vx = LEAF_SPEED_X;
		vy = LEAF_SPEED_Y;
		break;
	case LEAF_STATE_FALL_LEFT:
		timeTurn = GetTickCount64();
		vx = -LEAF_SPEED_X;
		vy = LEAF_SPEED_Y;
		break;
	}
}