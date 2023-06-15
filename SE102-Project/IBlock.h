#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_IBLOCK 17000


#define IBLOCK_WIDTH 15
#define IBLOCK_BBOX_WIDTH 15
#define IBLOCK_BBOX_HEIGHT 30

class IBlock : public CGameObject {
public:
	int type;
	IBlock(float x, float y, int Btype) : CGameObject(x, y) { type = Btype; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};
