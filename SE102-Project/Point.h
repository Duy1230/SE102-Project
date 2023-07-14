#pragma once

#pragma once

#include "GameObject.h"


#define ID_ANI_POINT 19000
#define POINT_BBOX_WIDTH 12
#define POINT_BBOX_HEIGHT 10

#define POINT_SPEED 0.01f
#define POINT_TIMEOUT 1000
#define COIN_SPARK_TIME_OUT 90
#define DUST_TIME_OUT 300

#define	DUST -3
#define COIN_SPARK -2
#define ONE_UP -1

#define POINT_100 0
#define POINT_200 1
#define POINT_400 2
#define POINT_800 3
#define POINT_1000 4
class CPoint : public CGameObject {
	int ID_Point;
	bool isMoving;
	ULONGLONG TimeAppear;
public:
	CPoint(float x, float y, int ID, bool setMoving = true) : CGameObject(x, y) {
		if (setMoving)
			vy = -POINT_SPEED;
		else
			vy = 0;
		ID_Point = ID;
		isMoving = setMoving;
		TimeAppear = GetTickCount64();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
