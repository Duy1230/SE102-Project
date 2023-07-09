#include "Koopas.h"
#include "Goomba.h"
#include "Flower.h"
#include "Fireball.h"
#include "Platform.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "IBlock.h"
#include "FGoomba.h"
#include "Point.h"

#include "Button.h"
#include "BrickButton.h"

#include "PlayScene.h"
#include "Game.h"


CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	aniID = ID_ANI_KOOPAS_WALKING_RIGHT;
	direction = 1;
	isPopingOut = 0;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	SetState(KOOPAS_STATE_WALKING_RIGHT);
}



void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH / 2;
	top = y - KOOPAS_BBOX_HEIGHT_STOP / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT_STOP;
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (dynamic_cast<CKoopas*>(e->obj)) {
		OnCollisionWithBoostKoopas(e);
		return;
	}
	
	else if (dynamic_cast<CPlatform*>(e->obj)) {
		OnCollisionWithPlatform(e);
		return;
	}

	else if (dynamic_cast<CBrick*>(e->obj)) {
		OnCollisionWithBrick(e);
		return;
	}
	
	else if (dynamic_cast<CGoomba*>(e->obj)) {
		if (e->obj->GetState() == GOOMBA_STATE_WALKING && state == KOOPAS_STATE_BOOST)
		{
			e->obj->SetState(GOOMBA_STATE_DIE_KOOPAS);
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), 0);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 20);
		}
			
		return;
	}

	else if (dynamic_cast<FGoomba*>(e->obj)) {
		if (e->obj->GetState() != FGOOMBA_STATE_DIE && state == KOOPAS_STATE_BOOST)
		{
			e->obj->SetState(FGOOMBA_STATE_DIE_KOOPAS);
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), 0);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 20);
		}
		return;
	}

	else if (dynamic_cast<CFlower*>(e->obj)) {
		if (state == KOOPAS_STATE_BOOST)
		{
			e->obj->Delete();
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), 0);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 20);
		}
		return;
	}

	else if (dynamic_cast<IBlock*>(e->obj)) {
		OnCollisionWithIBlock(e);
		return;
	}

	else if (dynamic_cast<CBrickButton*>(e->obj))
	{
		CBrickButton* b = dynamic_cast<CBrickButton*>(e->obj);
		if (state == KOOPAS_STATE_BOOST && b->AniID != ID_ANI_BRICK_BUTTON_COIN)
		{
			e->obj->Delete();
		}
	}
	
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
		return;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if ((state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT))
		{
			if (direction == 1)
			{
				aniID = ID_ANI_KOOPAS_WALKING_LEFT;
				direction = -1;
			}

			else
			{
				aniID = ID_ANI_KOOPAS_WALKING_RIGHT;
				direction = 1;
			}
		}
	}
	
	/*
	else if (dynamic_cast<CBrick*>(e->obj) && e->nx != 0 && state == KOOPAS_STATE_BOOST) {
		CBrick* b = dynamic_cast<CBrick*>(e->obj);
		vx = -vx;
		if (b->AniID == GBRICK_STATE_BREAK)
		{
			b->SetState(GBRICK_STATE_BREAK);
		}
	}
	*/

}

void CKoopas::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* p = dynamic_cast<CPlatform*>(e->obj);
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
		return;
	}
	else if (e->nx != 0)
	{
		
		if ((state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT))
		{
			if (direction == 1)
				this->SetState(KOOPAS_STATE_WALKING_LEFT);
			else
				this->SetState(KOOPAS_STATE_WALKING_RIGHT);
		}
		else
			vx = -vx;

	}
}

void CKoopas::OnCollisionWithBoostKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* Koopas = dynamic_cast<CKoopas*>(e->obj);

	if (Koopas->GetState() == KOOPAS_STATE_BOOST && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)) {

		this->SetState(KOOPAS_STATE_DESTROY);
		CGameObject* point = new CPoint(this->GetX(), this->GetY(), 1);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 20);
		return;
	}
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (e->ny != 0)
	{
		vy = 0;
		return;
	}

	if (state == KOOPAS_STATE_BOOST)
	{
		if (brick->AniID > ID_ANI_BRICK_NULL && e->nx != 0)
		{
			CMario* mario = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
			switch (brick->AniID)
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

				if (mario->Getlevel() == MARIO_LEVEL_SMALL)
				{
					CGameObject* mushroom = new CMushroom(brick->GetX(), brick->GetY(), MUSHROOM_TYPE_RED);
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom, brick->GetX(), brick->GetY() - 16);
				}
				else if (mario->Getlevel() >= MARIO_LEVEL_BIG)
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


			case ID_ANI_BRICK_MUSHROOM_GREEN:
			{
				CGameObject* mushroom = new CMushroom(brick->GetX(), brick->GetY(), MUSHROOM_TYPE_GREEN);
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom, brick->GetX(), brick->GetY() - 16);
			}
			}

			brick->AniID = ID_ANI_BRICK_NULL;
		}
		vx = -vx;
	}
	else if (e->nx != 0 && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT) )
	{
		if (direction == 1)
			this->SetState(KOOPAS_STATE_WALKING_LEFT);
		else
			this->SetState(KOOPAS_STATE_WALKING_RIGHT);
		//isDeleted = true;
		//return;
	}

}

void CKoopas::OnCollisionWithIBlock(LPCOLLISIONEVENT e)
{
	IBlock* p = dynamic_cast<IBlock*>(e->obj);
	if (p->type != 3 && p->type != -1)
		return;
	if (state == KOOPAS_STATE_BOOST)
		return;
	else
	{
		if (e->nx != 0)
		{
			if (direction == 1)
				this->SetState(KOOPAS_STATE_WALKING_LEFT);
			else
				this->SetState(KOOPAS_STATE_WALKING_RIGHT);
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == KOOPAS_STATE_STOP && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT * 0.8))
		isPopingOut = 1;
	if ((state == KOOPAS_STATE_STOP) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	{
		isPopingOut = 0;
		if (direction == 1)
			this->SetState(KOOPAS_STATE_WALKING_RIGHT);
		else
			this->SetState(KOOPAS_STATE_WALKING_LEFT);
		//isDeleted = true;
		//return;
	}
	if (state == KOOPAS_STATE_HELD)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		int marioLevel = mario->Getlevel();
		if (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT * 0.8)
			isPopingOut = 1;
		if (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT) {
			isPopingOut = 0;
			if (mario->GetNx() == 1)
			{
				this->x = mario->GetX() - 10;
				this->SetState(KOOPAS_STATE_WALKING_RIGHT);
			}
			else
			{
				this->x= mario->GetX() + 10;
				this->SetState(KOOPAS_STATE_WALKING_LEFT);
			}
				
			if (marioLevel == MARIO_LEVEL_FOX) {
				mario->isHolding = false;
				mario->SetLevel(MARIO_LEVEL_BIG);
				mario->StartUntouchable();
			}
			else if (marioLevel == MARIO_LEVEL_BIG)
			{
				mario->isHolding = false;
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->StartUntouchable();
			}
			else
			{
				mario->SetState(MARIO_STATE_DIE);
			}
		}
		else if (mario->isHolding == false) {
			if (mario->GetNx() == 1)
				this->x = mario->GetX() - 14;
			else
				this->x = mario->GetX() + 14;

			this->SetState(KOOPAS_STATE_BOOST);
		}
		else {
			if (mario->Getlevel() == MARIO_LEVEL_SMALL)
			{
				if (mario->GetNx() > 0)
				{
					x = mario->GetX() + 9;
					y = mario->GetY() - 2;
				}
				else {
					x = mario->GetX() - 9;
					y = mario->GetY() - 2;
				}
			}
			else
			{
				if (mario->GetNx() > 0)
				{
					x = mario->GetX() + 9;
					y = mario->GetY() + 2;
				}
				else {
					x = mario->GetX() - 9;
					y = mario->GetY() + 2;
				}
			}		
		}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}



void CKoopas::Render()
{
	switch (state)
	{
	case KOOPAS_STATE_WALKING_RIGHT:
		aniID = ID_ANI_KOOPAS_WALKING_RIGHT;
		break;

	case KOOPAS_STATE_WALKING_LEFT:
		aniID = ID_ANI_KOOPAS_WALKING_LEFT;
		break;

	case KOOPAS_STATE_BOOST:
		aniID = ID_ANI_KOOPAS_BOOST;
		break;

	case KOOPAS_STATE_DESTROY:
		aniID = ID_ANI_KOOPAS_STOP;
		break;
	default:
		if (isPopingOut)
			aniID = ID_ANI_KOOPAS_POP_OUT;
		else
			aniID = ID_ANI_KOOPAS_STOP;
	}

	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_STOP:
		die_start = GetTickCount64();
		//y += 5;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		
		direction = -1;
		this->ay = KOOPAS_GRAVITY;
		die_start = -1;
		vx = -KOOPAS_WALKING_SPEED;
		break;

	case KOOPAS_STATE_WALKING_RIGHT:
		
		direction = 1;
		this->ay = KOOPAS_GRAVITY;
		die_start = -1;
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_BOOST:
	{
		isPopingOut = 0;
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		//this->y -= 5;
		this->ax = 0;
		this->ay = KOOPAS_GRAVITY;
		die_start = -1;
		if (mario->GetNx() > 0)
			vx = 4 * KOOPAS_WALKING_SPEED;
		else
			vx = -4 * KOOPAS_WALKING_SPEED;
		vy = 0;
	}
	break;
	case KOOPAS_STATE_DESTROY:
		this->vy = -0.4f;
		this->vx = 0;
		this->ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_HELD:
	{
		//die_start = GetTickCount64();
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetNx() > 0)
		{
			x = mario->GetX() + 5;
			y = mario->GetY() - 5;
		}
		else {
			x = mario->GetX() - 5;
			y = mario->GetY() - 5;
		}
	}
	break;
	}
	CGameObject::SetState(state);
}