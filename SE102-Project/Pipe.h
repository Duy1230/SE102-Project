#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "Mario.h"
#include "PlayScene.h"

#define ID_ANI_PIPE 23000

#define PIPE_WIDTH 33
#define PIPE_BBOX_WIDTH 33
#define PIPE_BBOX_HEIGHT 49

#define PIPE_STATE_BLOCK 0
#define PIPE_STATE_NO_BLOCK 1

#define PIPE_TIME_CHANGE_BACK 500
#define PIPE_TUNNEL_SIZE 8
class CPipe : public CGameObject {
public:
	int state;
	ULONGLONG t;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 1; };
	int IsBlocking() { 
		return state == PIPE_STATE_BLOCK;
	}
	CPipe(float x, float y) : CGameObject(x, y) { state = PIPE_STATE_BLOCK; };
	void setState(int newstate)
	{
		state = newstate;
		t = GetTickCount64();
	}
};
