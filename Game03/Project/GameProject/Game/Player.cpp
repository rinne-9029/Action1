#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include"Effect.h"
#include"FireTrap.h"
#include"Map.h"



Player::Player(const CVector2D& p, bool flip):
	Base(eType_Player) {
		//画像複製
		m_img = COPY_RESOURCE("Player", CImage);
		//再生アニメーション設定
		m_img.ChangeAnimation(0);
		//座標設定
		m_pos_old = m_pos = p ;
		//中心位置設定
		m_img.SetCenter(28,32);
		//矩形判定の設定
		m_rect = CRect(-23, -30, 0,0);
		//反転フラグ
		m_flip = flip;
		//通常状態へ
		m_state = eState_Idle;
		//着地フラグ
		m_is_ground = true;
		//ヒットポイント
		m_hp = 100;
		//ジャンプ回数
        jumpcount = 0;
		//無敵時間
		invincibility = 0;

}



void Player::StateIdle()
{
	//移動量
	const float move_speed = 6;
	//ジャンプ力
    const float jump_pow = 12;
	//移動フラグ
	bool move_flag = false;

	//無敵時間
	invincibility -= 1;


	//左移動
	if (HOLD(CInput::eButton2)) {
		//移動量を設定
		m_pos.x += -move_speed;
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}

	//右移動
	if (HOLD(CInput::eButton4)) {
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}

	//２段ジャンプ
	//ジャンプの前に入れることによって１回目から２段ジャンプになるのを防ぐ
     if (!m_is_ground && PUSH(CInput::eButton5) && jumpcount == 0) {
			m_state = eState_DoubleJump;
		}



	//ジャンプ
	if (m_is_ground && PUSH(CInput::eButton5)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}
	
	//地面についたら
	if (m_is_ground) {
		jumpcount = 0;
	}

	//ジャンプ中なら
	if (!m_is_ground) {
		if (m_vec.y < 0)
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);

	
	}
	//移動中なら
	else
	{
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}
		
	}
}

//2段ジャンプ状態
void Player::StateDoubleJump()
{   //ジャンプ力
	const float jump_pow = 6;
	//アニメーション切り替え
	m_img.ChangeAnimation(eAnimDoubleJump,false);
	m_vec.y = -jump_pow;
	jumpcount += 1;
	//アニメーション終了後
 	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

//ダメージ状態
void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

//ダウン状態
void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}


void Player::Update()
{
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//2段ジャンプ状態
	case eState_DoubleJump:
		StateDoubleJump();
		break;
		//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
		//ダウン状態
	case eState_Down:
		StateDown();
		break;
}
	//落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;

	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;

		//アニメーション更新
	m_img.UpdateAnimation();
	//スクロール設定
	m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 980;
}


void Player::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形の表示
	//DrawRect();
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//ゴール判定
	case eType_Goal:
			if (Base::CollisionRect(this, b)) {
				b->SetKill();
			}
			break;
//火柱の当たり判定
	case eType_FireTrap:
			if (Base::CollisionRect(this,b) && invincibility<=0) {
				//無敵時間3秒
				invincibility = 180;
					m_hp -= 50;
					printf("当たった");
					if (m_hp <= 0) {
						m_state = eState_Down;
					}else {
						m_state = eState_Damage;
					}
		}
		break;
	case eType_Field:
		//Field型へキャスト、型変換できたら
		if(Map* m=dynamic_cast<Map*>(b)){
			int t = m->CollisionMap(CVector2D(m_pos.x,m_pos_old.y),m_rect);
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y),m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}
}