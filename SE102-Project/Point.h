#pragma once

#pragma once

#include "GameObject.h"


#define ID_ANI_POINT 19000
#define POINT_BBOX_WIDTH 12
#define POINT_BBOX_HEIGHT 10

#define POINT_SPEED 0.01f
#define POINT_TIMEOUT 1000

#define POINT_100 0
#define POINT_200 1
#define POINT_400 2
#define POINT_800 3
#define POINT_1000 4
class CPoint : public CGameObject {
	int ID_Point;
	ULONGLONG TimeAppear;
public:
	CPoint(float x, float y, int ID) : CGameObject(x, y) {
		vy = -POINT_SPEED;
		ID_Point = ID;
		TimeAppear = GetTickCount64();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
