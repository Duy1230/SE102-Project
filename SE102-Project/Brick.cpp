#include "Brick.h"
#include "Coin.h"


void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(this->AniID)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}



void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isMoving == 1 && (GetTickCount64() - timeDisplace > BRICK_TIME_DISPLACEMENT))
	{
		y--; displacement++;
		timeDisplace = GetTickCount64();
		if (displacement == BRICK_DISPLACEMENT)
		{
			isMoving = -1;
		}
	}

	else if (isMoving == -1 && (GetTickCount64() - timeDisplace > BRICK_TIME_DISPLACEMENT))
	{
		y++; displacement--;
		timeDisplace = GetTickCount64();
		if (displacement == 0)
		{
			isMoving = 0;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
