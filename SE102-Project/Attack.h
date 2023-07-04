#pragma once
#include "GameObject.h"


#define ATTACK_MOVING_SPEED 0.3f


#define ATTACK_BBOX_WIDTH 5
#define ATTACK_BBOX_HEIGHT 2

#define ATTACK_MOVE_TIMEOUT 50
#define ATTACK_STOP_TIMEOUT 100

#define ATTACK_STATE_MOVE 100
#define ATTACK_STATE_STOP 200

#define ID_ANI_ATTACK_MOVE 20000
#define ID_ANI_ATTACK_STOP 20001
class CAttack : public CGameObject
{
protected:

	ULONGLONG time_move;
	ULONGLONG disappear_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != ATTACK_STATE_STOP; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrickButton(LPCOLLISIONEVENT e);

public:
	CAttack(float x, float y);
	virtual void SetState(int state);
};
