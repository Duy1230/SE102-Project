#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_PIPE 23000

#define PIPE_WIDTH 33
#define PIPE_BBOX_WIDTH 33
#define PIPE_BBOX_HEIGHT 49



class CPipe : public CGameObject {
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }
	CPipe(float x, float y) : CGameObject(x, y) {};
};
