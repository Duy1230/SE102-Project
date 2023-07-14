#include "Card.h"
#include <cstdlib>
void CCard::Render()
{

	CAnimations::GetInstance()->Get(AniID)->Render(x, y);
}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BBOX_WIDTH / 2;
	t = y - CARD_BBOX_HEIGHT / 2;
	r = l + CARD_BBOX_WIDTH;
	b = t + CARD_BBOX_HEIGHT;
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCard::Collided()
{
	srand(time(NULL));
	vy = -CARD_SPEED;
	int random = rand() % 3 + 1;
	AniID += random;
}