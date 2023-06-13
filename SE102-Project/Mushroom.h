#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.05f

#define ID_ANI_MUSHROOM_NULL 14000
#define ID_ANI_MUSHROOM_APPEAR 14001


#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_STATE_INIT 100
#define MUSHROOM_STATE_MOVE 200

#define MUSHROOM_TIMEOUT 1800

class CMushroom : public CGameObject {
protected:
	float ax;
	float ay;

	ULONGLONG timeAppear;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y);
	virtual void SetState(int state);
};
