#pragma once

#include "GameObject.h"
#include "IBlock.h"
#include "Background.h"
#include "AssetIDs.h"

#include "Animation.h"
#include "Animations.h"



//ACTIONS TIME FOR TITLE SCREEN

#define TIME_TITLE_SCREEN_MOVE_CURTAIN 2000

class Controller : public CGameObject {
public:
	ULONGLONG timeLine;
	Controller(float x, float y) : CGameObject(x, y) {
		timeLine = GetTickCount64();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};
