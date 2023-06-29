#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.09f
#define MARIO_RUNNING_SPEED		0.15f

#define MARIO_ACCEL_WALK_X	0.00025f
#define MARIO_ACCEL_RUN_X	0.00003f

#define MARIO_JUMP_SPEED_Y		0.2f
#define MARIO_JUMP_RUN_SPEED_Y	0.2f
#define MARIO_FLY_UP_SPEED	0.14f

#define MARIO_GRAVITY			0.0004f

#define MARIO_JUMP_DEFLECT_SPEED  0.12f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HOLDING_RIGHT		550
#define MARIO_STATE_HOLDING_LEFT		551

#define MARIO_STATE_FLYING				650

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_HOLD_IDLE_LEFT 1010
#define ID_ANI_MARIO_HOLD_IDLE_RIGHT 1011

#define ID_ANI_MARIO_HOLD_WALKING_LEFT 1020
#define ID_ANI_MARIO_HOLD_WALKING_RIGHT 1021

#define ID_ANI_MARIO_HOLD_JUMP_LEFT 1030
#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 1031



#define ID_ANI_MARIO_DIE 999
#define ID_ANI_MARIO_INVINCIBLE 998

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 1610
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 1611

#define ID_ANI_MARIO_SMALL_HOLD_WALKING_LEFT 1620
#define ID_ANI_MARIO_SMALL_HOLD_WALKING_RIGHT 1621

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1630
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1631

//FOX MARIO
#define ID_ANI_MARIO_FOX_IDLE_RIGHT 2400
#define ID_ANI_MARIO_FOX_IDLE_LEFT 2401

#define ID_ANI_MARIO_FOX_WALKING_RIGHT 2500
#define ID_ANI_MARIO_FOX_WALKING_LEFT 2501

#define ID_ANI_MARIO_FOX_RUNNING_RIGHT 2600
#define ID_ANI_MARIO_FOX_RUNNING_LEFT 2601

#define ID_ANI_MARIO_FOX_JUMP_WALK_RIGHT 2700
#define ID_ANI_MARIO_FOX_JUMP_WALK_LEFT 2701

#define ID_ANI_MARIO_FOX_JUMP_RUN_RIGHT 2800
#define ID_ANI_MARIO_FOX_JUMP_RUN_LEFT 2801

#define ID_ANI_MARIO_FOX_SIT_RIGHT 2900
#define ID_ANI_MARIO_FOX_SIT_LEFT 2901

#define ID_ANI_MARIO_FOX_BRACE_RIGHT 3000
#define ID_ANI_MARIO_FOX_BRACE_LEFT 3001

#define ID_ANI_MARIO_FOX_HOLD_IDLE_LEFT 3010
#define ID_ANI_MARIO_FOX_HOLD_IDLE_RIGHT 3011

#define ID_ANI_MARIO_FOX_HOLD_WALKING_LEFT 3020
#define ID_ANI_MARIO_FOX_HOLD_WALKING_RIGHT 3021

#define ID_ANI_MARIO_FOX_HOLD_JUMP_LEFT 3030
#define ID_ANI_MARIO_FOX_HOLD_JUMP_RIGHT 3031

#define ID_ANI_MARIO_FOX_ATTACK_LEFT 3040
#define ID_ANI_MARIO_FOX_ATTACK_RIGHT 3041

#define ID_ANI_MARIO_FOX_FLAP_LEFT 3050
#define ID_ANI_MARIO_FOX_FLAP_RIGHT 3051

#define ID_ANI_MARIO_FOX_SLOW_FALLING_LEFT 3060
#define ID_ANI_MARIO_FOX_SLOW_FALLING_RIGHT 3061
#define ID_ANI_MARIO_FOX_SLOW_FALLING_LEFT_IDLE 3062
#define ID_ANI_MARIO_FOX_SLOW_FALLING_RIGHT_IDLE 3063
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FOX		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_FOX_BBOX_WIDTH  16
#define MARIO_FOX_BBOX_HEIGHT 24

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_FLY_TIME	5000

#define MARIO_ATTACK_TIME 230
#define MARIO_FLAP_TIME 150
#define MARIO_SLOW_FALLING_TIME 150

#define MARIO_UNTOUCHABLE_SPRITE_LOWERBOUND 8
#define MARIO_UNTOUCHABLE_SPRITE_UPPERBOUND 16

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isFlying;
	BOOLEAN slowFallingBegin;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	int combo;
	int level; 
	int untouchable; 
	int untouchable_spriteChange = 1;
	ULONGLONG untouchable_start;

	ULONGLONG isAttacking;
	ULONGLONG isFlapping;
	ULONGLONG isSlowFalling;

	ULONGLONG flyTime;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithFGoomba(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdFox();

public:
	BOOLEAN isHolding;
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		isHolding = false;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isAttacking = -1;
		isFlapping = -1;
		isSlowFalling = -1;
		flyTime = -1;
		isOnPlatform = false;
		isFlying = false;
		slowFallingBegin = false;
		coin = 0;
		combo = -1;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() {
		return 0;
	}//(state != MARIO_STATE_DIE && untouchable==0); }

	int Getlevel() { return level; }
	int GetNx() { return nx; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	int GetUntouchable() { return untouchable; }
	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	BOOLEAN IsFlying() { return isFlying; }
	void setAttacking();
	void setFlying();
	void setSlowFalling();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); untouchable_spriteChange = 1; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void addCoin() { coin++; }
};