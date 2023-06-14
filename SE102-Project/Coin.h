#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN_BASIC 11000
#define ID_ANI_COIN_1 11001
#define ID_ANI_COIN_Q 11002

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 9
#define COIN_BBOX_HEIGHT 16

#define QCOIN_STATE_INIT 100
#define QCOIN_STATE_FINAL 200
#define QCOIN_SPEED 0.3f
#define QCOIN_TIMEOUT 550

class CCoin : public CGameObject {
public:
	ULONGLONG goUp_begin = -1;
	int aniID;
	CCoin(float x, float y, int aniID) : CGameObject(x, y) { 
		this->aniID = aniID;
		if (this->aniID == ID_ANI_COIN_Q)
			this->SetState(QCOIN_STATE_FINAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void SetState(int state);
};