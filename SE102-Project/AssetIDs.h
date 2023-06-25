#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
//NEW
#define OBJECT_TYPE_FLOWER 6
#define OBJECT_TYPE_FIREBALL 7
#define OBJECT_TYPE_MUSHROOM 8
#define OBJECT_TYPE_LEAFL 9
#define OBJECT_TYPE_IBLOCK 10
#define OBJECT_TYPE_FGOOMBA 11
#define OBJECT_TYPE_POINT 12
#define OBJECT_TYPE_MARIO_ATTACK 13

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)

#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)

#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)

#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_BIG_HOLD (ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_HOLD_IDLE (ID_SPRITE_MARIO_BIG_HOLD + 10)
#define ID_SPRITE_MARIO_BIG_HOLD_IDLE_LEFT (ID_SPRITE_MARIO_BIG_HOLD_IDLE + 1)
#define ID_SPRITE_MARIO_BIG_HOLD_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_HOLD_IDLE + 2)
#define ID_SPRITE_MARIO_BIG_HOLD_WALK (ID_SPRITE_MARIO_BIG_HOLD + 20)
#define ID_SPRITE_MARIO_BIG_HOLD_WALK_LEFT (ID_SPRITE_MARIO_BIG_HOLD + 2)
#define ID_SPRITE_MARIO_BIG_HOLD_WALK_RIGHT (ID_SPRITE_MARIO_BIG_HOLD + 6)
#define ID_SPRITE_MARIO_BIG_HOLD_JUMP (ID_SPRITE_MARIO_BIG_HOLD + 30)
#define ID_SPRITE_MARIO_BIG_HOLD_JUMP_LEFT (ID_SPRITE_MARIO_BIG_HOLD + 1)
#define ID_SPRITE_MARIO_BIG_HOLD_JUMP_RIGHT (ID_SPRITE_MARIO_BIG_HOLD + 2)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)
#define ID_SPRITE_MARIO_INVINCIBLE (ID_SPRITE_MARIO + 3001)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)

#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)

#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_HOLD (ID_SPRITE_MARIO_SMALL + 700)
#define ID_SPRITE_MARIO_SMALL_HOLD_IDLE (ID_SPRITE_MARIO_SMALL_HOLD + 10)
#define ID_SPRITE_MARIO_SMALL_HOLD_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_HOLD_IDLE + 1)
#define ID_SPRITE_MARIO_SMALL_HOLD_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_HOLD_IDLE + 2)
#define ID_SPRITE_MARIO_SMALL_HOLD_WALK (ID_SPRITE_MARIO_SMALL_HOLD + 20)
#define ID_SPRITE_MARIO_SMALL_HOLD_WALK_LEFT (ID_SPRITE_MARIO_SMALL_HOLD + 2)
#define ID_SPRITE_MARIO_SMALL_HOLD_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_HOLD + 6)
#define ID_SPRITE_MARIO_SMALL_HOLD_JUMP (ID_SPRITE_MARIO_SMALL_HOLD + 30)
#define ID_SPRITE_MARIO_SMALL_HOLD_JUMP_LEFT (ID_SPRITE_MARIO_SMALL_HOLD + 1)
#define ID_SPRITE_MARIO_SMALL_HOLD_JUMP_RIGHT (ID_SPRITE_MARIO_SMALL_HOLD + 2)


#define ID_SPRITE_MARIO_FOX (ID_SPRITE_MARIO + 3000)
#define ID_SPRITE_MARIO_FOX_IDLE (ID_SPRITE_MARIO_FOX + 100)
#define ID_SPRITE_MARIO_FOX_IDLE_LEFT (ID_SPRITE_MARIO_FOX_IDLE + 10)
#define ID_SPRITE_MARIO_FOX_IDLE_RIGHT (ID_SPRITE_MARIO_FOX_IDLE + 20)

#define ID_SPRITE_MARIO_FOX_WALKING (ID_SPRITE_MARIO_FOX + 200)
#define ID_SPRITE_MARIO_FOX_WALKING_LEFT (ID_SPRITE_MARIO_FOX_WALKING + 10)
#define ID_SPRITE_MARIO_FOX_WALKING_RIGHT (ID_SPRITE_MARIO_FOX_WALKING + 20)

#define ID_SPRITE_MARIO_FOX_RUNNING (ID_SPRITE_MARIO_FOX + 300)
#define ID_SPRITE_MARIO_FOX_RUNNING_LEFT (ID_SPRITE_MARIO_FOX_RUNNING + 10)
#define ID_SPRITE_MARIO_FOX_RUNNING_RIGHT (ID_SPRITE_MARIO_FOX_RUNNING + 20)

#define ID_SPRITE_MARIO_FOX_JUMP (ID_SPRITE_MARIO_FOX + 400)
#define ID_SPRITE_MARIO_FOX_JUMP_WALK (ID_SPRITE_MARIO_FOX_JUMP + 10)
#define ID_SPRITE_MARIO_FOX_JUMP_WALK_LEFT (ID_SPRITE_MARIO_FOX_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_FOX_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_FOX_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_FOX_JUMP_RUN (ID_SPRITE_MARIO_FOX_JUMP + 20)
#define ID_SPRITE_MARIO_FOX_JUMP_RUN_LEFT (ID_SPRITE_MARIO_FOX_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_FOX_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_FOX_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_FOX_SIT (ID_SPRITE_MARIO_FOX + 500)
#define ID_SPRITE_MARIO_FOX_SIT_LEFT (ID_SPRITE_MARIO_FOX_SIT + 10)
#define ID_SPRITE_MARIO_FOX_SIT_RIGHT (ID_SPRITE_MARIO_FOX_SIT + 20)

#define ID_SPRITE_MARIO_FOX_BRACE (ID_SPRITE_MARIO_FOX + 600)
#define ID_SPRITE_MARIO_FOX_BRACE_LEFT (ID_SPRITE_MARIO_FOX_BRACE + 10)
#define ID_SPRITE_MARIO_FOX_BRACE_RIGHT (ID_SPRITE_MARIO_FOX_BRACE + 20)

#define ID_SPRITE_MARIO_FOX_HOLD (ID_SPRITE_MARIO_SMALL + 700)
#define ID_SPRITE_MARIO_FOX_HOLD_IDLE (ID_SPRITE_MARIO_SMALL_HOLD + 10)
#define ID_SPRITE_MARIO_FOX_HOLD_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_HOLD_IDLE + 1)
#define ID_SPRITE_MARIO_FOX_HOLD_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_HOLD_IDLE + 2)
#define ID_SPRITE_MARIO_FOX_HOLD_WALK (ID_SPRITE_MARIO_FOX_HOLD + 20)
#define ID_SPRITE_MARIO_FOX_HOLD_WALK_LEFT (ID_SPRITE_MARIO_FOX_HOLD + 2)
#define ID_SPRITE_MARIO_FOX_HOLD_WALK_RIGHT (ID_SPRITE_MARIO_FOX_HOLD + 6)
#define ID_SPRITE_MARIO_FOX_HOLD_JUMP (ID_SPRITE_MARIO_FOX_HOLD + 30)
#define ID_SPRITE_MARIO_FOX_HOLD_JUMP_LEFT (ID_SPRITE_MARIO_FOX_HOLD + 1)
#define ID_SPRITE_MARIO_FOX_HOLD_JUMP_RIGHT (ID_SPRITE_MARIO_FOX_HOLD + 2)

#define ID_SPRITE_MARIO_FOX_ATTACK (ID_SPRITE_MARIO_FOX + 800)
#define ID_SPRITE_MARIO_FOX_ATTACK_FRONT (ID_SPRITE_MARIO_FOX_ATTACK + 1)
#define ID_SPRITE_MARIO_FOX_ATTACK_BACK (ID_SPRITE_MARIO_FOX_ATTACK + 2)

#define ID_SPRITE_MARIO_FOX_FLY (ID_SPRITE_MARIO_FOX + 850)
#define ID_SPRITE_MARIO_FOX_FLY_RIGHT (ID_SPRITE_MARIO_FOX_FLY + 1)
#define ID_SPRITE_MARIO_FOX_FKY_LEFT (ID_SPRITE_MARIO_FOX_FLY + 3)
#pragma endregion 


#define ID_SPRITE_BRICK 20000
#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)
//NEW
#define ID_SPRITE_BACKGROUND (ID_SPRITE_CLOUD+4000)
#define ID_SPRITE_FLOWER 60000
#define ID_SPRITE_FIREBALL 70000
#define ID_SPRITE_MUSHROOM 71000
#define ID_SPRITE_LEAF 72000
#define ID_SPRITE_IBLOCK 73000
#define ID_SPRITE_FGOOMBA 74000
#define ID_SPRITE_POINT 75000
#define ID_SPRITE_ATTACK 76000
#define ID_SPRITE_KOOPAS 80000