#include "Background.h"

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MAP)->Render(x, y);

	//RenderBoundingBox();
}

void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x ;
	t = y ;
	r = l + 1;
	b = t + 1;
}

void CBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}