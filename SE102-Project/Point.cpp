#include "Point.h"

void CPoint::Render()
{
	int ID = ID_ANI_POINT + ID_Point;
	if (ID > 19004)
		ID = 19004;
	CAnimations::GetInstance()->Get(ID)->Render(x, y);
}

void CPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - POINT_BBOX_WIDTH / 2;
	t = y - POINT_BBOX_HEIGHT / 2;
	r = l + POINT_BBOX_WIDTH;
	b = t + POINT_BBOX_HEIGHT;
}

void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - TimeAppear > POINT_TIMEOUT)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}