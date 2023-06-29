#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BRICK_BUTTON_GLASSBRICK 22000
#define ID_ANI_BRICK_BUTTON_COIN 22001


#define BRICK_BUTTON_WIDTH 16
#define BRICK_BUTTON_BBOX_WIDTH 16
#define BRICK_BUTTON_BBOX_HEIGHT 16

class CBrickButton : public CGameObject {
public:
	int id;
	int AniID;
	CBrickButton(float x, float y, int aniID, int ID) : CGameObject(x, y) {
		this->id = ID;
		this->AniID = aniID;
	}
	void Render();
	int IsBlocking() { return AniID != ID_ANI_BRICK_BUTTON_COIN; };
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void ChangeState(int aniIDNew) { this->AniID = aniIDNew; };
	//get id
	int getID() { return id; }
};
