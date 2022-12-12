#include"Game.h"
#include"GameData.h"
#include"Player.h"
#include"Enemy.h"
#include"Goal.h"
#include"Map.h"
#include"UI.h"
#include"../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	//�X�e�[�W���Ƃ̃}�b�v�`�b�v��ǂݍ��ޏ���
	Base::Add(new Map(GameData::stage));
	//���Ԃ�ǂݍ��ޏ���
	Base::Add(new UI());
	//HP��ǂݍ��ޏ���
	Base::Add(new UI2());

}
Game::~Game()
{
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game::Update()
{
	//�S�[����������΃Q�[���V�[���I��
	if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}


