#pragma once
#include "Game.h"
#include "PlayScene.h"

#include "GameObject.h"
#include "IBlock.h"
#include "Background.h"
#include "AssetIDs.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Mario.h"

#include "Animation.h"
#include "Animations.h"



//ACTIONS TIME FOR TITLE SCREEN

#define TIME_TITLE_SCREEN_MOVE_CURTAIN 2000
#define TIME_TITLE_SCREEN_MOVE_TITLE 2800
#define TIME_TITLE_SCREEN_STOP_TITLE 3260
#define TIME_TITLE_SCREEN_TURN_BRIGHT 3600
#define TIME_TITLE_SCREEN_ADD_MARIO 4500
#define TIME_TITLE_SCREEN_MARIO_MOVE_RIGHT 7000
#define TIME_TITLE_SCREEN_MARIO_MOVE_LEFT 8000
#define TIME_TITLE_SCREEN_MARIO_STOP 8500
#define TIME_TITLE_SCREEN_MARIO_JUMP 11000
#define TIME_TITLE_SCREEN_MARIO_TAIL_FLAP 11500
#define TIME_TITLE_SCREEN_MARIO_FINAL 13000

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
