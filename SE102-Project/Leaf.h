#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define LEAF_SPEED_MOVEUP 0.07f
#define LEAF_SPEED_X 0.09f
#define LEAF_SPEED_Y 0.02f

#define ID_ANI_LEAF_FALL_RIGHT 15000
#define ID_ANI_LEAF_FALL_LEFT 15001


#define LEAF_BBOX_WIDTH 17
#define LEAF_BBOX_HEIGHT 15

#define LEAF_STATE_MOVEUP 100
#define LEAF_STATE_FALL_RIGHT 200
#define LEAF_STATE_FALL_LEFT 300

#define LEAF_TIME_MOVEUP 500
#define LEAF_TIME_TURN 500

class CLeaf : public CGameObject {
protected:
	ULONGLONG timeMoveup;
	ULONGLONG timeTurn;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }

public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};

