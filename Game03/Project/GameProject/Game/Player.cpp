#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include"Effect.h"
#include"FireTrap.h"
#include"Map.h"



Player::Player(const CVector2D& p, bool flip):
	Base(eType_Player) {
		//�摜����
		m_img = COPY_RESOURCE("Player", CImage);
		//�Đ��A�j���[�V�����ݒ�
		m_img.ChangeAnimation(0);
		//���W�ݒ�
		m_pos_old = m_pos = p ;
		//���S�ʒu�ݒ�
		m_img.SetCenter(28,32);
		//��`����̐ݒ�
		m_rect = CRect(-23, -30, 0,0);
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

}



void Player::StateIdle()
{
	//�ړ���
	const float move_speed = 6;
	//�W�����v��
    const float jump_pow = 12;
	//�ړ��t���O
	bool move_flag = false;

	//���G����
	invincibility -= 1;


	//���ړ�
	if (HOLD(CInput::eButton2)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}

	//�E�ړ�
	if (HOLD(CInput::eButton4)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}

	//�Q�i�W�����v
	//�W�����v�̑O�ɓ���邱�Ƃɂ���ĂP��ڂ���Q�i�W�����v�ɂȂ�̂�h��
     if (!m_is_ground && PUSH(CInput::eButton5) && jumpcount == 0) {
			m_state = eState_DoubleJump;
		}



	//�W�����v
	if (m_is_ground && PUSH(CInput::eButton5)) {
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
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

//�_�E�����
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
	m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 980;
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
		//�S�[������
	case eType_Goal:
			if (Base::CollisionRect(this, b)) {
				b->SetKill();
			}
			break;
//�Β��̓����蔻��
	case eType_FireTrap:
			if (Base::CollisionRect(this,b) && invincibility<=0) {
				//���G����3�b
				invincibility = 180;
					m_hp -= 50;
					printf("��������");
					if (m_hp <= 0) {
						m_state = eState_Down;
					}else {
						m_state = eState_Damage;
					}
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