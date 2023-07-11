#include "Flower.h"
#include "Fireball.h"
#include "Mario.h"

#include "PlayScene.h"
#include "Game.h"


void CFlower::InitPoints()
{
	pointOfInterest[0] = x - 30.0f;
	pointOfInterest[1] = y + 30.0f;
	pointOfInterest[2] = x - 40.0f;
	pointOfInterest[3] = y;
	pointOfInterest[4] = x - 30.0f;
	pointOfInterest[5] = y - 30.0f;
	pointOfInterest[6] = x;
	pointOfInterest[7] = y - 40.0f;
	pointOfInterest[8] = x + 30.0f;
	pointOfInterest[9] = y - 30.0f;
	pointOfInterest[10] = x + 40.0f;
	pointOfInterest[11] = y;
	pointOfInterest[12] = x + 30.0f;
	pointOfInterest[13] = y + 30.0f;
}

void CFlower::calculateDistance() {
	float mario_x = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetX();
	float mario_y = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetY();
	for (int i = 0; i < 7; i++) {
		distance[i] = sqrt((mario_x - pointOfInterest[2 * i]) * (mario_x - pointOfInterest[2 * i]) + (mario_y - pointOfInterest[2 * i + 1]) * (mario_y - pointOfInterest[2 * i + 1]));
	}
}

int CFlower::findDirection() {
	float min = distance[0];
	int index = 0;
	for (int i = 1; i < 7; i++) {
		if (distance[i] < min)
		{
			min = distance[i];
			index = i;
		}
	}
	return 2 * index;
}

CFlower::CFlower(float x, float y,int Ftype) :CGameObject(x, y)
{
	type = Ftype;
	vx = 0;
	this->InitPoints();
	state = FLOWER_STATE_MOVEUP;
}

void CFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FLOWER_BBOX_WIDTH / 2;
	t = y - FLOWER_BBOX_HEIGHT / 2;
	r = l + FLOWER_BBOX_WIDTH;
	b = t + FLOWER_BBOX_HEIGHT;
}


void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_MOVEUP:
		timeMove = GetTickCount64();
		vy = FLOWER_SPEED;
		break;
	case FLOWER_STATE_STOP_UP:
		timeStop = GetTickCount64();
		vy = 0;
		break;
	case FLOWER_STATE_STOP_DOWN:
		timeStop = GetTickCount64();
		vy = 0;
		break;
	case FLOWER_STATE_MOVEDOWN:
		timeMove = GetTickCount64();
		vy = -FLOWER_SPEED;
		break;
	}
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	if ((state == FLOWER_STATE_STOP_UP) && (GetTickCount64() - timeStop > FLOWER_STOP_TIME))
	{
		state = FLOWER_STATE_MOVEDOWN;
		this->SetState(state);
	}
	else if ((state == FLOWER_STATE_MOVEUP) && (GetTickCount64() - timeMove > FLOWER_MOVE_TIME))
	{
		state = FLOWER_STATE_STOP_UP;
		this->SetState(state);
	}
	else if ((state == FLOWER_STATE_MOVEDOWN) && (GetTickCount64() - timeMove > FLOWER_MOVE_TIME))
	{
		state = FLOWER_STATE_STOP_DOWN;
		this->SetState(state);

		float mario_x = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetX();
		float mario_y = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetY();

		if ((sqrt((mario_x - x) * (mario_x - x) + (mario_y - y) * (mario_y - y)) < 200.0f) && type != 2 ) {
			InitPoints();
			calculateDistance();
			int directionIndex = findDirection();

			float fireball_vx = (pointOfInterest[directionIndex] - x) / FIREBALL_FLOWER_SPEED_SCALING;
			float fireball_vy = (pointOfInterest[directionIndex + 1] - y) / FIREBALL_FLOWER_SPEED_SCALING;

			CGameObject* fireball = new CFireBall(x, y, fireball_vx, fireball_vy);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(fireball, x, y);
		}
		
	}
	else if ((state == FLOWER_STATE_STOP_DOWN) && (GetTickCount64() - timeStop > FLOWER_STOP_TIME))
	{
		state = FLOWER_STATE_MOVEUP;
		this->SetState(state);
		
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlower::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == FLOWER_STATE_STOP_DOWN) {
		switch (type)
		{
		case 0:
			animations->Get(ID_ANI_FLOWER_RED + 1)->Render(x, y);
			break;
		case 1:
			animations->Get(ID_ANI_FLOWER_GREEN + 1)->Render(x, y);
			break;
		default:
			animations->Get(ID_ANI_FLOWER_GREEN_NO_FIREBALL)->Render(x, y);
		}
	}
	else {
		switch (type)
		{
		case 0:
			animations->Get(ID_ANI_FLOWER_RED)->Render(x, y);
			break;
		case 1:
			animations->Get(ID_ANI_FLOWER_GREEN)->Render(x, y);
			break;
		default:
			animations->Get(ID_ANI_FLOWER_GREEN_NO_FIREBALL)->Render(x, y);
		}
	}
	

	//RenderBoundingBox();
}