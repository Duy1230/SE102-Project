#include "Button.h"

#include "PlayScene.h"


CButton::CButton(float x, float y, int ID):CGameObject(x, y)
{
	this->SetState(BUTTON_STATE_INIT);
	this->id = ID;
}

void CButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BUTTON_STATE_PRESSED)
	{
		left = x - BUTTON_BBOX_WIDTH / 2;
		top = y - BUTTON_BBOX_HEIGHT_PRESSED / 2;
		right = left + BUTTON_BBOX_WIDTH;
		bottom = top + BUTTON_BBOX_HEIGHT_PRESSED;
	}
	else
	{
		left = x - BUTTON_BBOX_WIDTH / 2;
		top = y - BUTTON_BBOX_HEIGHT / 2;
		right = left + BUTTON_BBOX_WIDTH;
		bottom = top + BUTTON_BBOX_HEIGHT;
	}
}


void CButton::Render()
{
	int aniId = ID_ANI_BUTTON_INIT;
	if (state == BUTTON_STATE_PRESSED)
	{
		aniId = ID_ANI_BUTTON_PRESSED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BUTTON_STATE_INIT:
		break;
	case BUTTON_STATE_PRESSED:
		y += 6;
		break;
	}
}