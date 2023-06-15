#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_IBLOCK 17000


#define IBLOCK_WIDTH 15
#define IBLOCK_BBOX_WIDTH 15
#define IBLOCK_BBOX_HEIGHT 15

class IBlock : public CGameObject {
public:
	IBlock(float x, float y) : CGameObject(x, y) {};
	
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};
