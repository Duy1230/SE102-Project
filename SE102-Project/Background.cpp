#include "Background.h"

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x ;
	t = y ;
	r = l + 1;
	b = t + 1;
}

void CBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBackground::SetAniID()
{
	switch (this->type)
	{
	case ID_TYPE_MAP:
		aniID = ID_ANI_MAP;
		break;

	case ID_TYPE_TITLE_BACKGROUND:
		aniID = ID_ANI_TITLE_BACKGROUND;
		break;

	case ID_TYPE_CURTAIN_BACKGROUND:
		aniID = ID_ANI_CURTAIN_BACKGROUND;
		break;
	}
}

void CBackground::SetType(int new_type)
{
	this->type = new_type;
	this->SetAniID();
}

void CBackground::SetState(int IDtype, int state)
{
	vector<LPGAMEOBJECT> objects = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->getObjects();
	for (size_t i = 1; i < objects.size(); i++)
	{
		if (dynamic_cast<CBackground*>(objects[i]))
		{
			CBackground* obj = dynamic_cast<CBackground*>(objects[i]);
			switch (obj->type)
			{
			case ID_TYPE_CURTAIN_BACKGROUND:
				obj->SetCurtainState(state);
				break;
			}
		}

	}
}

void CBackground::SetCurtainState(int state)
{
	switch (state)
	{
	case STATE_CURTAIN_MOVE:
		vy = -CURTAIN_SPEED_Y;
		break;
	}
}

