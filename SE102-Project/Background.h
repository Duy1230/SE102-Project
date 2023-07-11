#pragma once

#include "GameObject.h"


#define ID_ANI_MAP 24000

class CBackground : public CGameObject {
public:
	CBackground(float x, float y, float v_x = 0, float v_y = 0) : CGameObject(x, y) {
		vx = v_x;
		vy = v_y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};

