#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include"Effect.h"
#include"FireTrap.h"
#include"Map.h"
#include"GameData.h"
#include"Fallingfloor.h"



Player::Player(int id, int layer,const CVector2D& p, bool flip):
	Base(eType_Player,layer) {
		//画像複製
		m_img = COPY_RESOURCE("Player", CImage);
		//再生アニメーション設定
		m_img.ChangeAnimation(0);
		//座標設定
		m_pos_old = m_pos = p ;
		//キャラの画像サイズ
		m_img.SetSize(32, 32);
		//中心位置設定
		m_img.SetCenter(16,32);
		//矩形判定の設定
		m_rect = CRect(-10, -32,10,0);
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
		//プレイヤーの振り分け
		m_player_id = id;
		

}



void Player::StateIdle()
{
	//移動量
	const float move_speed = 4;
	//ジャンプ力
    const float jump_pow = 8;
	//移動フラグ
	bool move_flag = false;

	//1フレームごとに無敵時間減少
	invincibility -= 1;


	//左移動
	if (HOLD_PAD(m_player_id,CInput::eLeft) && m_pos.x >= 15) {
		//移動量を設定
		m_pos.x += -move_speed;
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}

	//右移動
	if (HOLD_PAD(m_player_id,CInput::eRight) && m_pos.x <= 2540) {
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}

	//２段ジャンプ
	//ジャンプの前に入れることによって１回目から２段ジャンプになるのを防ぐ
     if (!m_is_ground && PUSH_PAD(m_player_id,CInput::eButton1) && jumpcount == 0) {
			m_state = eState_DoubleJump;
		}



	//ジャンプ
	if (m_is_ground && PUSH_PAD(m_player_id,CInput::eButton1)) {
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
	m_img.ChangeAnimation(eAnimDamage,false);	
	if (m_img.CheckAnimationEnd()) {
        GameData::s_kosu -= 1;
		m_state = eState_Idle;
	}
}

//ダウン状態
void Player::StateDown()
{
	    GameData::s_kosu -= 1;
		Base::Add(new Effect(m_layer,"Effect_Desappearing", m_pos + CVector2D(0, -40), m_flip));
		SetKill();
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
	if( m_pos.x >= 1280/3 && m_pos.x <= 2560-1496){
		m_scroll[m_layer].x = m_pos.x - 1280 / 3;
	}
    m_scroll[m_layer].y = 600;
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
		//ゴールに当たった処理
	case eType_Goal:
			if (Base::CollisionRect(this, b)) {
				b->SetKill();
			}
			break;

			//ニードルに当たった処理
	case eType_Spike:
		if (Base::CollisionRect(this, b) && invincibility <= 0) {
			//無敵時間1秒
			invincibility = 60;
			m_hp -= 20;
			if (m_hp <= 0) {
				m_state = eState_Down;
			}
			else {
				m_state = eState_Damage;
			}
		}
		break;

//火柱に当たった処理
	case eType_FireTrap:
			if (Base::CollisionRect(this,b) && invincibility<=0) {
				//無敵時間1秒
				invincibility = 60;
					m_hp -= 20;
					if (m_hp <= 0) {
						m_state = eState_Down;
					}else {
						m_state = eState_Damage;
					}
		}
		break;

		//アイテムに当たった処理
	case eType_Item:
		if (Base::CollisionRect(this, b)) {
			jumpcount = 0;
		}
		break;

        //落ちる床の上に乗る
	case eType_Fallingfloor:
		if (Base::CollisionRect(this, b)) {
			
			m_pos.x = m_pos_old.x;
            m_vec.y = 0;
			m_is_ground = true;
		}
		break;

		//スタート位置の上に乗る
	case eType_Start:
		if (Base::CollisionRect(this, b)) {
			m_pos.y = m_pos_old.y;
			m_vec.y = 0;
			m_is_ground = true;
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