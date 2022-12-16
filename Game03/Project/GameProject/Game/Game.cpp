#include"Game.h"
#include"GameData.h"
#include"Map.h"
#include"UI.h"
#include"../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	int player_size =2;
	if (player_size == 1) {
		//�X�e�[�W���Ƃ̃}�b�v�`�b�v��ǂݍ��ޏ���
		Base::Add(new Map(GameData::stage, 0, Base::eLayer_Default));
		//���Ԃ�ǂݍ��ޏ���
		Base::Add(new UI(Base::eLayer_Default));
		//HP��ǂݍ��ޏ���
		Base::Add(new UI2(Base::eLayer_Default));
	}else {
		//�X�e�[�W���Ƃ̃}�b�v�`�b�v��ǂݍ��ޏ���
		Base::Add(new Map(GameData::stage, 0, Base::eLayer_Top));
		//���Ԃ�ǂݍ��ޏ���
		Base::Add(new UI(Base::eLayer_Top));
		//HP��ǂݍ��ޏ���
		Base::Add(new UI2(Base::eLayer_Top));


		//�X�e�[�W���Ƃ̃}�b�v�`�b�v��ǂݍ��ޏ���
		Base::Add(new Map(GameData::stage, 1, Base::eLayer_Bottom));
		//���Ԃ�ǂݍ��ޏ���
		Base::Add(new UI(Base::eLayer_Bottom));
		//HP��ǂݍ��ޏ���
		Base::Add(new UI2(Base::eLayer_Bottom));
	}
	
	
	

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
	if (!Base::FindObject(eType_Goal,Base::eLayer_Top)) {
		SetKill();
	}
	//�v���C���[1P���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player,Base::eLayer_Top ) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}


