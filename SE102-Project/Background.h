#pragma once

#include "GameObject.h"
#include "PlayScene.h"
//############################################# ANIMATION ####################################
#define ID_ANI_MAP 24000

#define ID_ANI_TITLE_BACKGROUND	24010
#define ID_ANI_TITLE_BACKGROUND_BRIGHT	24011

#define ID_ANI_CURTAIN_BACKGROUND 24020

#define ID_ANI_GAME_TITLE 24030

#define ID_ANI_3 24040
#define ID_ANI_3_FLASHY 24041

//############################################# TYPE #########################################
#define ID_TYPE_MAP 0

#define ID_TYPE_TITLE_BACKGROUND 10
#define ID_TYPE_TITLE_BACKGROUND_BRIGHT 11

#define ID_TYPE_CURTAIN_BACKGROUND 20

#define ID_TYPE_GAME_TITLE 30

#define ID_TYPE_3 40
#define ID_TYPE_3_FLASHY 41

//BACKGROUND INFORMATION
//state:
#define TURN_BLACK 10
#define TURN_BRIGHT 11


//CURTAIN INFORMATION
//state:
#define STATE_CURTAIN_MOVE 0
//velocity:
#define CURTAIN_SPEED_Y 0.08f

//TITLE INFORMATION
//states:
#define STATE_TITLE_MOVE 0
#define STATE_TITLE_STOP 1
//velocity:
#define TITLE_SPEED_Y 0.3f

//3 INFORMATION
//states:
#define STATE_THREE_MOVE 0
#define STATE_THREE_STOP 1
#define TURN_FLASHY 10
//velocity:
#define THREE_SPEED_Y 0.3f

class CBackground : public CGameObject {
public:
	int type;
	int aniID;
	CBackground(float x, float y, int btype, float v_x = 0, float v_y = 0) : CGameObject(x, y) {
		vx = v_x;
		vy = v_y;
		type = btype;
		SetAniID();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void SetAniID();
	void SetType(int new_type);

	void SetState(int type, int state);

	void SetBackgroundState(int state);
	void SetCurtainState(int state);
	void SetTitleState(int state);
	void SetThreeState(int state);

};

