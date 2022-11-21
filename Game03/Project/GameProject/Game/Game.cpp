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
	Base::Add(new UI());

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
		GameData::s_count = 0;
	}
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
		GameData::s_count = 0;
	}
}


