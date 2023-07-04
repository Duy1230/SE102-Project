#include "Attack.h"
#include "Platform.h"
#include "Mario.h"
#include "Goomba.h"
#include "FGoomba.h"
#include "Flower.h"
#include "Brick.h"
#include "Koopas.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Point.h"
#include "BrickButton.h"
#include "Button.h"

#include "PlayScene.h"
#include "Game.h"



CAttack::CAttack(float x, float y) :CGameObject(x, y)
{
	disappear_start = -1;
	time_move = -1;
	SetState(ATTACK_STATE_MOVE);
}

void CAttack::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ATTACK_BBOX_WIDTH / 2;
	top = y - ATTACK_BBOX_HEIGHT / 2;
	right = left + ATTACK_BBOX_WIDTH;
	bottom = top + ATTACK_BBOX_HEIGHT;
}

void CAttack::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		OnCollisionWithEnemy(e);
		e->obj->SetState(GOOMBA_STATE_DIE_KOOPAS);
	}

	else if (dynamic_cast<FGoomba*>(e->obj))
	{
		OnCollisionWithEnemy(e);
		e->obj->SetState(FGOOMBA_STATE_DIE_KOOPAS);
	}
	else if (dynamic_cast<CFlower*>(e->obj))
	{
		OnCollisionWithEnemy(e);
		CFlower* f = dynamic_cast<CFlower*>(e->obj);
		f->Delete();
	}
	else if (dynamic_cast<CKoopas*>(e->obj))
	{
		OnCollisionWithEnemy(e);
		e->obj->SetState(KOOPAS_STATE_DESTROY);
	}
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CBrickButton*>(e->obj))
		OnCollisionWithBrickButton(e);

}

void CAttack::OnCollisionWithEnemy(LPCOLLISIONEVENT e)
{
	this->SetState(ATTACK_STATE_STOP);
	CGameObject* point = new CPoint(this->GetX(), this->GetY(), POINT_100);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, e->obj->GetX(), e->obj->GetY() - 30);
}

void CAttack::OnCollisionWithBrickButton(LPCOLLISIONEVENT e)
{
	CBrickButton* brick = dynamic_cast<CBrickButton*>(e->obj);
	CMario* mario = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
	float timeTorchBrick;

	if (mario->GetNx() > 0)
		timeTorchBrick = ATTACK_MOVE_TIMEOUT / 2;
	else
		timeTorchBrick = ATTACK_MOVE_TIMEOUT / 1.6;

	if (brick->AniID == ID_ANI_BRICK_BUTTON_GLASSBRICK && e->nx != 0 && GetTickCount64() - time_move < timeTorchBrick)
		brick->Delete();
}

void CAttack::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	CMario* mario = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
	float timeTorchBrick;

	if (mario->GetNx() > 0)
		timeTorchBrick = ATTACK_MOVE_TIMEOUT / 2;
	else
		timeTorchBrick = ATTACK_MOVE_TIMEOUT / 1.6;

	if (brick->AniID > ID_ANI_BRICK_NULL && e->nx != 0 && GetTickCount64() - time_move < timeTorchBrick)
	{
		int animationID = (int)brick->AniID;
		if (brick->AniID != ID_ANI_BRICK_BUTTON)
			brick->isMoving = 1;
		switch (animationID)
		{
		case ID_ANI_BRICK_COIN:
		{
			CGameObject* Ccoin = new CCoin(brick->GetX(), brick->GetY(), ID_ANI_COIN_Q);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(Ccoin, brick->GetX(), brick->GetY() + 10);
			mario->addCoin();
		}
		break;

		case ID_ANI_BRICK_MUSHROOM:
		{
			int state = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->Getlevel();

			if (state == MARIO_LEVEL_SMALL)
			{
				CGameObject* mushroom = new CMushroom(brick->GetX(), brick->GetY());
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom, brick->GetX(), brick->GetY() - 16);
			}
			else if (state >= MARIO_LEVEL_BIG)
			{
				CGameObject* leaf = new CLeaf(brick->GetX(), brick->GetY());
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(leaf, brick->GetX(), brick->GetY() - 16);
			}

		}
		break;
		case ID_ANI_BRICK_BUTTON:
		{
			CGameObject* button = new CButton(brick->GetX(), brick->GetY(), brick->getID());
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(button, brick->GetX(), brick->GetY() - 16);
		}
		break;

		}
		brick->AniID = ID_ANI_BRICK_NULL;

	}


}

void CAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (GetTickCount64() - time_move > ATTACK_MOVE_TIMEOUT && state == ATTACK_STATE_MOVE)
	{
		isDeleted = true;
		return;
	}

	else if (GetTickCount64() - disappear_start > ATTACK_STOP_TIMEOUT && state == ATTACK_STATE_STOP)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CAttack::Render()
{
	int aniId = ID_ANI_ATTACK_MOVE;
	if (state == ATTACK_STATE_STOP)
	{
		aniId = ID_ANI_ATTACK_STOP;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CAttack::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ATTACK_STATE_MOVE:
	{
		int direction = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetNx();
		vx = direction * ATTACK_MOVING_SPEED;
		time_move = GetTickCount64();
		break;
	}
		
	case ATTACK_STATE_STOP:
		time_move = -1;
		disappear_start = GetTickCount64();
		vx = 0;
		break;
	}
}