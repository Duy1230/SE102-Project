#pragma once
#pragma once
#include "GameObject.h"

#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"
#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_WALKING_SPEED 0.05f

#define KOOPAS_FLY_SPEED_X 0.05f
#define KOOPAS_FLY_SPEED_Y 0.35f

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
#define KOOPAS_STATE_KNOCK 600

#define ID_ANI_KOOPAS_WALKING_RIGHT 16000
#define ID_ANI_KOOPAS_WALKING_LEFT 16001
#define ID_ANI_KOOPAS_STOP 16002
#define ID_ANI_KOOPAS_POP_OUT 16003
#define ID_ANI_KOOPAS_BOOST 16004
#define ID_ANI_KOOPAS_STOP_UP 16005
#define ID_ANI_KOOPAS_POP_OUT_UP 16006
#define ID_ANI_KOOPAS_BOOST_UP 16007

class CKoopas : public CGameObject
{
protected:
	int aniID;
	int direction;
	float ax;
	float ay;
	bool isPopingOut;
	bool isLieUp;
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
	virtual void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithIBlock(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
	virtual void LieUp();
};
