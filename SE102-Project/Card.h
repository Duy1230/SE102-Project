#pragma once

#pragma once

#include "GameObject.h"


#define ID_ANI_CARD 26000

#define ID_ANI_CARD_TEXT 26004

#define CARD_BBOX_WIDTH 17
#define CARD_BBOX_HEIGHT 17

#define CARD_SPEED 0.15f


class CCard : public CGameObject {
public:
	int AniID;
	CCard(float x, float y, int newAniID = ID_ANI_CARD) : CGameObject(x, y) {
		vx = 0;
		vy = 0; 
		AniID = newAniID;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Collided();
	void SetAniID(int newAniId) { AniID = newAniId; }
	void Stop() { vy = 0; }
};

