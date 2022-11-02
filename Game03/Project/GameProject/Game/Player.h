#pragma once
#include"../Base/Base.h"

class Player : public Base {
private:
	//状態
	enum {
		eState_Idle,
		eState_DoubleJump,
		eState_Damage,
		eState_Down
	};
	//状態変数
	int m_state;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//ヒットポイント
	int m_hp;
	//ジャンプ回数
	int jumpcount;
	//無敵時間
	int invincibility;
	CImage m_img;

	//各状態での挙動
	void StateIdle();
	void StateDoubleJump();
	void StateDamage();
	void StateDown();

public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};