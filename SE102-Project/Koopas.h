#pragma once
#pragma once
#include "GameObject.h"

#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"
#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f


#define KOOPAS_BBOX_WIDTH 17
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_STOP 16

#define KOOPAS_DIE_TIMEOUT 10000

#define KOOPAS_STATE_WALKING_RIGHT 100
#define KOOPAS_STATE_WALKING_LEFT 101
#define KOOPAS_STATE_STOP 200
#define KOOPAS_STATE_BOOST 300
#define KOOPAS_STATE_DESTROY 400
#define KOOPAS_STATE_HELD 500

#define ID_ANI_KOOPAS_WALKING_RIGHT 16000
#define ID_ANI_KOOPAS_WALKING_LEFT 16001
#define ID_ANI_KOOPAS_STOP 16002
#define ID_ANI_KOOPAS_POP_OUT 16003
#define ID_ANI_KOOPAS_BOOST 16004

class CKoopas : public CGameObject
{
protected:
	int aniID;
	int direction;
	float ax;
	float ay;
	bool onSpecialBrick;
	ULONGLONG die_start;
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		return state != KOOPAS_STATE_DESTROY;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBoostKoopas(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBoostPlatform(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
};
