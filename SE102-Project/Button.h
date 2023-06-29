#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BUTTON_INIT 21000
#define ID_ANI_BUTTON_PRESSED 21001


#define BUTTON_BBOX_WIDTH 14
#define BUTTON_BBOX_HEIGHT 18
#define BUTTON_BBOX_HEIGHT_PRESSED 6

#define BUTTON_STATE_INIT 100
#define BUTTON_STATE_PRESSED 200


class CButton : public CGameObject {
protected:
	int id;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }

public:
	CButton(float x, float y, int id);
	virtual void SetState(int state);
};
