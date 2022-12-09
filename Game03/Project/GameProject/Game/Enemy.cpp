#include "Enemy.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"
#include "Map.h"
Enemy::Enemy(const CVector2D& p, bool flip) :
	Base(eType_Enemy) {
	//画像複製
	m_img = COPY_RESOURCE("Enemy", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	m_img.SetCenter(128, 224);
	//当たり判定用短形設定
	m_rect = CRect(-32, -128, 32, 0);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//ヒットポイント
	m_hp = 100;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
}

void Enemy::StateIdle()
{//移動量
	const float move_speed = 4;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;
	//プレイヤーを探索
	Base* player = Base::FindObject(eType_Player);

	//動作確認後コメント化（敵の移動）

		//左移動
	if (player) {
		if (player->m_pos.x < m_pos.x - 64) {
			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		else
			//右移動
			if (player->m_pos.x > m_pos.x + 64) {
				//移動量を設定
				m_pos.x += move_speed;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}
			else {
				//攻撃状態へ移行
				m_state = eState_Attack;
				m_attack_no++;
			}
	}
	
	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	}
	{
		//カウント0で待機状態へ
		if (--m_cnt <= 0) {
			//待機時間3秒～5秒
			m_cnt = rand() % 120 + 180;
			//Wait状態に変更
			m_state = eState_Wait;
		}
	}
}
void Enemy::StateAttack() {
	//攻撃アニメーション変更
	//m_img.ChangeAnimation(eAnimAttack01, false);
	//3番目のパターンなら
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			//Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			//Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Wait;
	}
}
void Enemy::StateWait() {
	//待機アニメーション
	m_img.ChangeAnimation(eAnimIdle);
	//カウント0で通常状態へ
	if (--m_cnt <= 0) {
		//待機時間3秒～5秒
		m_cnt = rand() % 120 + 180;
		
		m_state = eState_Idle;
	}
}

void Enemy::StateDown()
{
	//ダウンアニメーションへ変更
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		//Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}
}

void Enemy::StateDamage()
{//ダメージアニメーションへ変更
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}


void Enemy::Update()
{
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
	case eState_Down:
		StateDown();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Wait:
		StateWait();
		break;
	case eState_Attack:
		StateAttack();
		break;
	}

	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	//アニメーション更新
	m_img.UpdateAnimation();
}

void Enemy::Draw()
{//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形
	DrawRect();
}

void Enemy::Collision(Base* b)
{
	switch (b->m_type) {
		//攻撃オブジェクトとの判定
	case eType_Player_Attack:
		//Slash型へキャスト、型変換できたら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;
	case eType_Field:
		if(Map* m = dynamic_cast<Map*>(b)){
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y));
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y));
			if(t!=0){
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
		}
}
break;
	}
}
