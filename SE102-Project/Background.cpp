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
	
	case ID_TYPE_TITLE_BACKGROUND_BRIGHT:
		aniID = ID_ANI_TITLE_BACKGROUND_BRIGHT;
		break;

	case ID_TYPE_CURTAIN_BACKGROUND:
		aniID = ID_ANI_CURTAIN_BACKGROUND;
		break;

	case ID_TYPE_GAME_TITLE:
		aniID = ID_ANI_GAME_TITLE;
		break;

	case ID_TYPE_3:
		aniID = ID_ANI_3;
		break;

	case ID_TYPE_3_FLASHY:
		aniID = ID_ANI_3_FLASHY;
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
			case ID_TYPE_TITLE_BACKGROUND:
				if (obj->type == IDtype)
					obj->SetBackgroundState(state);
				break;

			case ID_TYPE_CURTAIN_BACKGROUND:
				if(obj->type == IDtype)
					obj->SetCurtainState(state);
				break;

			case ID_TYPE_GAME_TITLE:
				if (obj->type == IDtype)
					obj->SetTitleState(state);
				break;

			case ID_TYPE_3:
				if (obj->type == IDtype)
					obj->SetThreeState(state);
				break;
			}
		}

	}
}

void CBackground::SetBackgroundState(int state)
{
	switch (state)
	{
	case TURN_BLACK:
		SetType(ID_TYPE_TITLE_BACKGROUND);
		break;

	case TURN_BRIGHT:
		SetType(ID_TYPE_TITLE_BACKGROUND_BRIGHT);
		break;
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

void CBackground::SetTitleState(int state)
{
	switch (state)
	{
	case STATE_TITLE_MOVE:
		vy = TITLE_SPEED_Y;
		break;

	case STATE_TITLE_STOP:
		vy = 0;
		break;
	}
}

void CBackground::SetThreeState(int state)
{
	switch (state)
	{
	case STATE_THREE_MOVE:
		vy = THREE_SPEED_Y;
		break;

	case STATE_THREE_STOP:
		vy = 0;
		break;
	case TURN_FLASHY:
		SetType(ID_TYPE_3_FLASHY);
		return;
	}
}

