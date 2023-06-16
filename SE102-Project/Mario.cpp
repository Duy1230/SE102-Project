#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"

#include "Brick.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Fireball.h"
#include "Flower.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Koopas.h"
#include "FGoomba.h"
#include "Point.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_spriteChange = 0;
		untouchable_start = 0;
		untouchable = 0;
	}
	else
	{
		untouchable_spriteChange++;
	}

	

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
			combo = -1;
		}
	}
	else
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CFlower*>(e->obj))
		OnCollisionWithFlower(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<FGoomba*>(e->obj))
		OnCollisionWithFGoomba(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			isOnPlatform = false;
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			combo += 1;
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), combo);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_FOX)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					isSitting = false;
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithFGoomba(LPCOLLISIONEVENT e)
{
	FGoomba* goomba = dynamic_cast<FGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == FGOOMBA_STATE_WALKING)
		{
			isOnPlatform = false;
			goomba->SetState(FGOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			combo += 1;
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), combo);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
		}
		else if (goomba->GetState() == FGOOMBA_STATE_DIE)
			return;
		else
		{
			isOnPlatform = false;
			goomba->SetState(FGOOMBA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			combo += 1;
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), combo);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != FGOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_FOX)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					isSitting = false;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);


	if (e->ny < 0)
	{
		if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
		{
			isOnPlatform = false;
			koopas->SetState(KOOPAS_STATE_STOP);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			combo += 1;
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), combo);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
		}

		else if (koopas->GetState() == KOOPAS_STATE_BOOST)
		{
			isOnPlatform = false;
			koopas->SetState(KOOPAS_STATE_STOP);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			combo += 1;
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), combo);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
		}

		else {
			isOnPlatform = false;
			koopas->SetState(KOOPAS_STATE_BOOST);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			combo += 1;
			CGameObject* point = new CPoint(this->GetX(), this->GetY(), combo);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 10);
		}
	}

	else if (e->nx != 0 && koopas->GetState() == KOOPAS_STATE_STOP)
	{
		if (state == MARIO_STATE_HOLDING_LEFT || state == MARIO_STATE_HOLDING_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_HELD);
			isHolding = true;
		}
		else
		{
			koopas->SetState(KOOPAS_STATE_BOOST);
			isHolding = false;
		}
			
	}

	

	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_STOP)
			{
				if (level == MARIO_LEVEL_FOX)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					isSitting = false;
					StartUntouchable();
				}
				else
				{
					SetState(MARIO_STATE_DIE);
				}
			}
		}

	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* b = dynamic_cast<CCoin*>(e->obj);
	if (b->aniID != ID_ANI_COIN_Q)
	{
		e->obj->Delete();
		coin++;
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{

	e->obj->Delete();
	this->level = MARIO_LEVEL_FOX;
	y -= 4;
	CGameObject* point = new CPoint(this->GetX(), this->GetY(), 4);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* m = dynamic_cast<CMushroom*>(e->obj);
	if (m->GetState() != MUSHROOM_STATE_INIT)
	{
		e->obj->Delete();
		this->level = MARIO_LEVEL_BIG;
		y -= 6;
		CGameObject* point = new CPoint(this->GetX(), this->GetY(), 4);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(point, this->GetX(), this->GetY() - 30);
	}

}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (brick->AniID > ID_ANI_BRICK_NULL && e->ny > 0)
	{
		int animationID = (int)brick->AniID;
		switch (animationID)
		{
		case ID_ANI_BRICK_COIN:
		{
			CGameObject* Ccoin = new CCoin(brick->GetX(), brick->GetY(), ID_ANI_COIN_Q);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(Ccoin, brick->GetX(), brick->GetY() + 10);
			coin++;
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
			else if(state >= MARIO_LEVEL_BIG )
			{
				CGameObject* leaf = new CLeaf(brick->GetX(), brick->GetY());
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(leaf, brick->GetX(), brick->GetY() - 16);
			}
			
		}
		break;

		}
		brick->AniID = ID_ANI_BRICK_NULL;
		
	}

	
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{

	if (untouchable == 0 )
	{
		if (level == MARIO_LEVEL_FOX)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			isSitting = false;
			StartUntouchable();
		}
		else
		{
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithFlower(LPCOLLISIONEVENT e)
{

	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_FOX)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			isSitting = false;
			StartUntouchable();
		}
		else
		{
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X && !isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else if (isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting && isHolding == false)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHolding)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALKING_RIGHT;
				}
				else
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALKING_LEFT;
				}
				else
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for fox Mario
//
int CMario::GetAniIdFox()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X && !isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_FOX_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_FOX_JUMP_RUN_LEFT;
		}
		else if (isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_FOX_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_FOX_HOLD_JUMP_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_FOX_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_FOX_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting && isHolding==false)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_FOX_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_FOX_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHolding)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_FOX_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_FOX_HOLD_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_FOX_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_FOX_IDLE_LEFT;
				}		
			}
			else if (vx > 0)
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_FOX_HOLD_WALKING_RIGHT;
				}
				else
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_FOX_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_FOX_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_FOX_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_FOX_HOLD_WALKING_LEFT;
				}
				else
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_FOX_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_FOX_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_FOX_WALKING_LEFT;
				}			
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_FOX_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X && !isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else if (isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting && isHolding == false)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHolding)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_HOLD_WALKING_RIGHT;
				}
				else
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isHolding)
				{
					aniId = ID_ANI_MARIO_HOLD_WALKING_LEFT;
				}
				else
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (untouchable_spriteChange > MARIO_UNTOUCHABLE_SPRITE_LOWERBOUND)
	{
		aniId = ID_ANI_MARIO_INVINCIBLE;
		if (untouchable_spriteChange >= MARIO_UNTOUCHABLE_SPRITE_UPPERBOUND)
			untouchable_spriteChange = 0;
	}
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_FOX)
		aniId = GetAniIdFox();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			isOnPlatform = false;
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;

		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_HOLDING_RIGHT:
		//isHolding = true;
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;

	case MARIO_STATE_HOLDING_LEFT:
		//isHolding = true;
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		/*
		else if (isHolding)
		{
			if (state == MARIO_STATE_HOLDING_LEFT)
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
			else
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;

		}
		*/
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_FOX)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_FOX_BBOX_WIDTH / 2;
			top = y - MARIO_FOX_BBOX_HEIGHT / 2;
			right = left + MARIO_FOX_BBOX_WIDTH;
			bottom = top + MARIO_FOX_BBOX_HEIGHT;
		}
	}
	else
	{
		/*
		if (isHolding)
		{
			if (state == MARIO_STATE_HOLDING_LEFT)
				left = x - MARIO_SMALL_BBOX_WIDTH / 2;
			else
				left = x - MARIO_SMALL_BBOX_WIDTH / 2;
			top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
			right = left + MARIO_SMALL_BBOX_WIDTH;
			bottom = top + MARIO_SMALL_BBOX_HEIGHT;

		}
		*/
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

