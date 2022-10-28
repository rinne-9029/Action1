#include "AnimData.h"


static TexAnim playerIdle[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
	{ 5,2 },
	{ 6,2 },
	{ 7,2 },
	{ 8,2 },
	{ 9,2 },
	{ 10,2 },
};

static TexAnim playerRun[] = {
	{ 12,2 },
	{ 13,2 },
	{ 14,2 },
	{ 15,2 },
	{ 16,2 },
	{ 17,2 },
	{ 18,2 },
	{ 19,2 },
	{ 20,2 },
	{ 21,2 },
	{ 22,2 },
	{ 23,2 },
};

static TexAnim playerJumpUp[] = {
	{ 24,1 },
};

static TexAnim playerJumpDown[] = {
	{ 25,1 },
};

static TexAnim playerDoubleJump[] = {
	{ 26,1 },
	{ 27,1 },
	{ 28,1 },
	{ 29,1 },
	{ 30,1 },
	{ 31,1 },
};

static TexAnim playerWallJump[] = {
	{ 36,1 },
	{ 37,1 },
	{ 38,1 },
	{ 39,1 },
	{ 40,1 },
};
//�����܂ŃA�j���[�V��������

static TexAnim playerDamage[] = {
	{ 88,2 },
	{ 89,2 },
	{ 90,2 },
	{ 91,2 },
};
static TexAnim playerDamageEnd[] = {
	{ 92,2 },
	{ 93,2 },
	{ 94,2 },
	{ 95,2 },
};
static TexAnim playerDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};

static TexAnim playerDown[] = {
	{ 104,4 },
	{ 105,4 },
	{ 106,4 },
	{ 107,4 },
	{ 108,4 },
};
static TexAnim playerDownGround[] = {
	{ 109,4 },
	{ 110,4 },
	{ 111,4 },
};
static TexAnim playerWakeup[] = {
	{ 112,4 },
	{ 113,4 },
	{ 114,4 },
	{ 115,4 },
	{ 116,4 },
	{ 117,4 },
	{ 118,4 },
};
static TexAnim playerGuard[] = {
	//	{ 120,4 },
	//	{ 121,4 },
	{ 122,4 },
};
static TexAnim playerGuardEnd[] = {
	{ 122,4 },
	{ 121,4 },
	{ 120,4 },
};
static TexAnim playerCrash[] = {
	{ 128,4 },
	{ 129,4 },
	{ 130,4 },
	{ 131,90 },
};
static TexAnim playerCrash01End[] = {
	{ 131,4 },
	{ 130,4 },
	{ 129,4 },
	{ 128,4 },
};

TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdle),
	ANIMDATA(playerRun),
	ANIMDATA(playerJumpUp),
	ANIMDATA(playerJumpDown),
	ANIMDATA(playerDoubleJump),
	ANIMDATA(playerWallJump),
	ANIMDATA(playerDamage),
	ANIMDATA(playerDamageEnd),
	ANIMDATA(playerDeath),
	ANIMDATA(playerDown),
	ANIMDATA(playerDownGround),
	ANIMDATA(playerWakeup),
	ANIMDATA(playerGuard),
	ANIMDATA(playerGuardEnd),
	ANIMDATA(playerCrash),
	ANIMDATA(playerCrash01End),
};

static TexAnim enemyIdle[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
	{ 5,2 },
	{ 6,2 },
	{ 7,2 },
	{ 8,2 },
	{ 9,2 },
	{ 10,2 },
	{ 11,2 },
	{ 12,2 },
	{ 13,2 },
	{ 14,2 },
};
static TexAnim enemyRun[] = {
	{ 16,2 },
	{ 17,2 },
	{ 18,2 },
	{ 19,2 },
	{ 20,2 },
	{ 21,2 },
	{ 22,2 },
	{ 23,2 },
	{ 24,2 },
	{ 25,2 },
	{ 26,2 },
	{ 27,2 },
	{ 28,2 },
	{ 29,2 },
	{ 30,2 },
};
static TexAnim enemyJumpUp[] = {
	{ 0,0 },
};
static TexAnim enemyJumpDown[] = {
	{ 0,0 },
};

static TexAnim enemyAttack01[] = {
	{ 40,4 },
	{ 41,4 },
	{ 42,4 },
	{ 43,8 },
	{ 44,2 },
	{ 45,3 },
	{ 46,3 },
	{ 47,3 },
};
static TexAnim enemyAttack01End[] = {
	{ 48,2 },
	{ 49,2 },
	{ 50,2 },
	{ 51,2 },
	{ 52,2 },
};
static TexAnim enemyAttack02[] = {
	{ 0,0 },
};
static TexAnim enemyAttack02End[] = {
	{ 0,0 },
};
static TexAnim enemyAttack03[] = {
	{ 0,0 },
};
static TexAnim enemyAttack03End[] = {
	{ 0,0 },
};
static TexAnim enemyDamage[] = {
	{ 88,2 },
	{ 89,2 },
	{ 90,2 },
	{ 91,2 },
};
static TexAnim enemyDamageEnd[] = {
	{ 92,2 },
	{ 93,2 },
	{ 94,2 },
	{ 95,2 },
};
static TexAnim enemyDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};

static TexAnim enemyDown[] = {
	{ 104,4 },
	{ 105,4 },
	{ 106,4 },
	{ 107,4 },
	{ 108,4 },
};
static TexAnim enemyDownGround[] = {
	{ 109,4 },
	{ 110,4 },
	{ 111,4 },
};
static TexAnim enemyWakeup[] = {
	{ 112,4 },
	{ 113,4 },
	{ 114,4 },
	{ 115,4 },
	{ 116,4 },
	{ 117,4 },
	{ 118,4 },
};
static TexAnim enemyGuard[] = {
	{ 0,4 },
};
static TexAnim enemyGuardEnd[] = {
	{ 0,4 },
};
static TexAnim enemyCrash[] = {
	{ 128,4 },
	{ 129,4 },
	{ 130,4 },
	{ 131,60 },
};
static TexAnim enemyCrash01End[] = {
	{ 131,4 },
	{ 130,4 },
	{ 129,4 },
	{ 128,4 },
};
static TexAnim enemyExt01Attack[] = {
	{ 0,4 },
};
static TexAnim enemyExtAttack01End[] = {
	{ 0,4 },
};
TexAnimData enemy_anim_data[] = {
	ANIMDATA(enemyIdle),
	ANIMDATA(enemyRun),
	ANIMDATA(enemyJumpUp),
	ANIMDATA(enemyJumpDown),
	ANIMDATA(enemyAttack01),
	ANIMDATA(enemyAttack01End),
	ANIMDATA(enemyAttack02),
	ANIMDATA(enemyAttack02End),
	ANIMDATA(enemyAttack03),
	ANIMDATA(enemyAttack03End),
	ANIMDATA(enemyDamage),
	ANIMDATA(enemyDamageEnd),
	ANIMDATA(enemyDeath),
	ANIMDATA(enemyDown),
	ANIMDATA(enemyDownGround),
	ANIMDATA(enemyWakeup),
	ANIMDATA(enemyGuard),
	ANIMDATA(enemyGuardEnd),
	ANIMDATA(enemyCrash),
	ANIMDATA(enemyCrash01End),
	ANIMDATA(enemyExt01Attack),
	ANIMDATA(enemyExtAttack01End),
};




static TexAnim _effect_blood[] = {
	{ 0,1 },
	{ 1,1 },
	{ 2,1 },
	{ 3,1 },
};
TexAnimData effect_blood_anim_data[] = {
	ANIMDATA(_effect_blood),
};
static TexAnim _effect_smoke[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_smoke_anim_data[] = {
	ANIMDATA(_effect_smoke),
};

static TexAnim _effect_bomb[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_bomb_anim_data[] = {
	ANIMDATA(_effect_smoke),
};
static TexAnim _effect_slash[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
	{ 3,4 },
	{ 4,4 },
};
TexAnimData effect_slash_anim_data[] = {
	ANIMDATA(_effect_slash),
};