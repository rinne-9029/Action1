#pragma once
#include <GLLibrary.h>

//!アニメーションの種類
enum  {
	eAnimIdle = 0,
	eAnimRun,
	eAnimJumpUp,
	eAnimJumpDown,
	eAnimDoubleJump,
	eAnimWallJump,
	eAnimDamage,
	eAnimDeath,
	eAnimDown,
	eAnimAttack01,
	eAnimAttack01End,
	eAnimDownGround,
	eAnimWakeUp,
	eAnimGuard,
	eAnimGuardEnd,
	eAnimCrash,
	eAnimCrashEnd,
	eAnimExtAttack01,
	eAnimExtAttack01End,
	eAnimExtAttack02,
	eAnimExtAttack02End,
	eAnimStep,
};

//プレイヤーのアニメーションデータ
extern TexAnimData player_anim_data[];
//敵のアニメーションデータ
extern TexAnimData enemy_anim_data[];
//エフェクトのアニメーションデータ
extern TexAnimData effect_blood_anim_data[];
extern TexAnimData effect_smoke_anim_data[];
extern TexAnimData effect_slash_anim_data[];
extern TexAnimData effect_bomb_anim_data[];
extern TexAnimData effect_desappearing_anim_data[];