#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FLOWER 12000
#define	FLOWER_WIDTH 10
#define FLOWER_BBOX_WIDTH 17
#define FLOWER_BBOX_HEIGHT 33

#define FLOWER_STATE_MOVEUP 100
#define FLOWER_STATE_MOVEDOWN 200
#define FLOWER_STATE_STOP_UP 300
#define FLOWER_STATE_STOP_DOWN 400

#define FLOWER_SPEED 0.02f
#define FLOWER_STOP_TIME 2000
#define FLOWER_MOVE_TIME 1800

#define FIREBALL_FLOWER_SPEED_SCALING 600
class CFlower : public CGameObject {
public:
	float distance[7];
	float pointOfInterest[14];

	ULONGLONG timeMove;
	ULONGLONG timeStop;

	void InitPoints();
	void calculateDistance();
	int findDirection();

	CFlower(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Delete() { isDeleted = true; }
	virtual void SetState(int state);
};

