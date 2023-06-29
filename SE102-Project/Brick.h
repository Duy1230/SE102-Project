#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BRICK 9999
#define ID_ANI_BRICK_NULL 10000
#define ID_ANI_BRICK_COIN 10001
#define ID_ANI_BRICK_MUSHROOM 10002
#define ID_ANI_BRICK_BUTTON 10003


#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_DISPLACEMENT 3
#define BRICK_TIME_DISPLACEMENT 50
class CBrick : public CGameObject {
public:
	int id;
	int AniID;
	int displacement = 0;
	int isMoving = 0;
	ULONGLONG timeDisplace = -1;
	CBrick(float x, float y, int aniID) : CGameObject(x, y) {
		int static ID = 0;
		this->id = ID;
		this->AniID = aniID;
		ID++;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//get id
	int getID() { return id; }
};
