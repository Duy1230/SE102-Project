#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	float width;
	float height; 
	float location_x;
	float location_y;
public:
	CPortal(float l, float t, float r, float b, int scene_id, float lx, float ly);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	float GetLx() { return location_x; }
	float GetLy() { return location_y; }
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};