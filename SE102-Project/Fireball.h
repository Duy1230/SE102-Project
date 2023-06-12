#pragma once

#include "GameObject.h"


#define ID_ANI_FIREBALL 13000

#define	FIREBALL_WIDTH 10
#define FIREBALL_BBOX_WIDTH 9
#define FIREBALL_BBOX_HEIGHT 8

class CFireBall : public CGameObject {
public:
	CFireBall(float x, float y, float v_x = 0, float v_y = 0) : CGameObject(x, y) {
		vx = v_x;
		vy = v_y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);
};
