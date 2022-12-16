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
		//�摜����
		m_img = COPY_RESOURCE("Player", CImage);
		//�Đ��A�j���[�V�����ݒ�
		m_img.ChangeAnimation(0);
		//���W�ݒ�
		m_pos_old = m_pos = p ;
		//�L�����̉摜�T�C�Y
		m_img.SetSize(32, 32);
		//���S�ʒu�ݒ�
		m_img.SetCenter(16,32);
		//��`����̐ݒ�
		m_rect = CRect(-10, -32,10,0);
		//���]�t���O
		m_flip = flip;
		//�ʏ��Ԃ�
		m_state = eState_Idle;
		//���n�t���O
		m_is_ground = true;
		//�q�b�g�|�C���g
		m_hp = 100;
		//�W�����v��
        jumpcount = 0;
		//���G����
		invincibility = 0;
		//�v���C���[�̐U�蕪��
		m_player_id = id;
		

}



void Player::StateIdle()
{
	//�ړ���
	const float move_speed = 4;
	//�W�����v��
    const float jump_pow = 8;
	//�ړ��t���O
	bool move_flag = false;

	//1�t���[�����Ƃɖ��G���Ԍ���
	invincibility -= 1;


	//���ړ�
	if (HOLD_PAD(m_player_id,CInput::eLeft) && m_pos.x >= 15) {
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}

	//�E�ړ�
	if (HOLD_PAD(m_player_id,CInput::eRight) && m_pos.x <= 2540) {
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}

	//�Q�i�W�����v
	//�W�����v�̑O�ɓ���邱�Ƃɂ���ĂP��ڂ���Q�i�W�����v�ɂȂ�̂�h��
     if (!m_is_ground && PUSH_PAD(m_player_id,CInput::eButton1) && jumpcount == 0) {
			m_state = eState_DoubleJump;
		}



	//�W�����v
	if (m_is_ground && PUSH_PAD(m_player_id,CInput::eButton1)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}
	
	//�n�ʂɂ�����
	if (m_is_ground) {
		jumpcount = 0;
	}

	//�W�����v���Ȃ�
	if (!m_is_ground) {
		if (m_vec.y < 0)
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//���~�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpDown, false);

	
	}
	//�ړ����Ȃ�
	else
	{
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimIdle);
		}
		
	}
}

//2�i�W�����v���
void Player::StateDoubleJump()
{   //�W�����v��
	const float jump_pow = 6;
	//�A�j���[�V�����؂�ւ�
	m_img.ChangeAnimation(eAnimDoubleJump,false);
	m_vec.y = -jump_pow;
	jumpcount += 1;
	//�A�j���[�V�����I����
 	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

//�_���[�W���
void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage,false);	
	if (m_img.CheckAnimationEnd()) {
        GameData::s_kosu -= 1;
		m_state = eState_Idle;
	}
}

//�_�E�����
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
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//2�i�W�����v���
	case eState_DoubleJump:
		StateDoubleJump();
		break;
		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;
		//�_�E�����
	case eState_Down:
		StateDown();
		break;
}
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;

	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;

		//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�X�N���[���ݒ�
	if( m_pos.x >= 1280/3 && m_pos.x <= 2560-1496){
		m_scroll[m_layer].x = m_pos.x - 1280 / 3;
	}
    m_scroll[m_layer].y = 600;
}


void Player::Draw()
{
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//�����蔻���`�̕\��
	//DrawRect();
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//�S�[���ɓ�����������
	case eType_Goal:
			if (Base::CollisionRect(this, b)) {
				b->SetKill();
			}
			break;

			//�j�[�h���ɓ�����������
	case eType_Spike:
		if (Base::CollisionRect(this, b) && invincibility <= 0) {
			//���G����1�b
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

//�Β��ɓ�����������
	case eType_FireTrap:
			if (Base::CollisionRect(this,b) && invincibility<=0) {
				//���G����1�b
				invincibility = 60;
					m_hp -= 20;
					if (m_hp <= 0) {
						m_state = eState_Down;
					}else {
						m_state = eState_Damage;
					}
		}
		break;

		//�A�C�e���ɓ�����������
	case eType_Item:
		if (Base::CollisionRect(this, b)) {
			jumpcount = 0;
		}
		break;

        //�����鏰�̏�ɏ��
	case eType_Fallingfloor:
		if (Base::CollisionRect(this, b)) {
			
			m_pos.x = m_pos_old.x;
            m_vec.y = 0;
			m_is_ground = true;
		}
		break;

		//�X�^�[�g�ʒu�̏�ɏ��
	case eType_Start:
		if (Base::CollisionRect(this, b)) {
			m_pos.y = m_pos_old.y;
			m_vec.y = 0;
			m_is_ground = true;
		}
		break;

	case eType_Field:
		//Field�^�փL���X�g�A�^�ϊ��ł�����
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