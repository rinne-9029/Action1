#include"Game.h"
#include"Field.h"
#include"Player.h"
#include"Enemy.h"
#include"Goal.h"
#include"Start.h"
#include"Map.h"
#include"Fallingfloor.h"
#include"FireTrap.h"
#include"../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Map());
	//�v���C���[�z�u
	Base::Add(new Player(CVector2D(MAP_TIP_SIZE * 3, MAP_TIP_SIZE * 20), false));
	//�G�z�u
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 1, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//�S�[���z�u
	Base::Add(new Goal(CVector2D(MAP_TIP_SIZE * 9, MAP_TIP_SIZE * 18)));
	//�X�^�[�g�z�u
	Base::Add(new Start(CVector2D(MAP_TIP_SIZE * 3, MAP_TIP_SIZE * 21)));
	//�����鏰�z�u
	Base::Add(new Fallingfloor(CVector2D(MAP_TIP_SIZE * 10, MAP_TIP_SIZE * 17)));
	//�Β��̔z�u
	Base::Add(new FireTrap(CVector2D(MAP_TIP_SIZE * 12, MAP_TIP_SIZE * 17),false));




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


