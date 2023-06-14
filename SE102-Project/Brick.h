#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BRICK 9999
#define ID_ANI_BRICK_NULL 10000
#define ID_ANI_BRICK_COIN 10001
#define ID_ANI_BRICK_MUSHROOM 10002
#define ID_ANI_BRICK_LEAF 10003


#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 15

class CBrick : public CGameObject {
public:
	int AniID;
	CBrick(float x, float y, int aniID) : CGameObject(x, y) {
		this->AniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};