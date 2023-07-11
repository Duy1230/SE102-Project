#pragma once

#include "GameObject.h"
#include "IBlock.h"

#define ID_ANI_MINIMARIO 25000

#define MINIMARIO_BBOX_WIDTH 5
#define MINIMARIO_BBOX_HEIGHT 5

#define MINIMARIO_SPEED 0.08f

#define MINIMARIO_STATE_STOP -1
#define MINIMARIO_STATE_MOVE_LEFT 0
#define MINIMARIO_STATE_MOVE_UP 1
#define MINIMARIO_STATE_MOVE_RIGHT 2
#define MINIMARIO_STATE_MOVE_DOWN 3

class CMiniMario : public CGameObject {
public:
	int level[5] = { 2, 4, 5, 8, 11 };

	int route[12][4] = {
		{-1, -1, 1, -1},
		{0, 2, -1, -1},
		{-1, -1, 3, 1},
		{2, -1, 4, -1},
		{3, -1, 5, 9},
		{4, -1, 6, -1},
		{5, -1, -1, 7},
		{8, 6, -1, -1},
		{9, -1, 7, -1},
		{-1, 4, 8, 10},
		{11, 9,-1, -1},
		{-1, -1, 10, -1}
	};

	int current_node;
	bool isMoving;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	CMiniMario(float x, float y) : CGameObject(x, y) {
		isMoving = false;
		current_node = 0;
		vx = 0;
		vy = 0;
	}
	//Greater than 0 mean we can go in that direction
	int canMoveLeft();
	int canMoveRight();
	int canMoveUp();
	int canMoveDown();
	bool canEnter();

	void SetState(int state);
	void SetNode(int new_node) { current_node = new_node; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
};
