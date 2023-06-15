#pragma once

#include "GameObject.h"

#define FGOOMBA_GRAVITY 0.0005f
#define FGOOMBA_WALKING_SPEED 0.05f
#define FGOOMBA_JUMP_SPEED 0.1f


#define FGOOMBA_BBOX_WIDTH 16
#define FGOOMBA_BBOX_HEIGHT 14
#define FGOOMBA_BBOX_HEIGHT_DIE 6

#define FGOOMBA_DIE_TIMEOUT 800
#define FGOOMBA_DIE_TIMEOUT_KOOPAS 1000
#define FGOOMBA_STATE_TIMEOUT 1000

#define FGOOMBA_STATE_WALKING 100
#define FGOOMBA_STATE_WALKING_WITH_WING 200
#define FGOOMBA_STATE_DIE 300
#define FGOOMBA_STATE_DIE_KOOPAS 301
#define FGOOMBA_STATE_FLYING 500

#define ID_ANI_FGOOMBA_WALKING 18000
#define ID_ANI_FGOOMBA_DIE 18001
#define ID_ANI_FGOOMBA_WALKING_WITH_WING 18002
#define ID_ANI_FGOOMBA_PREPARE_FLYING 18003
#define ID_ANI_FGOOMBA_FLY 18004


class FGoomba : public CGameObject
{
protected:
	BOOLEAN isOnPlatform;
	int jumpStep;
	float ax;
	float ay;
	ULONGLONG stateChangeTime;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != FGOOMBA_STATE_DIE_KOOPAS; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	FGoomba(float x, float y);
	virtual void SetState(int state);
};
