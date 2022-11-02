#include"Game.h"
#include"Field.h"
#include"Player.h"
#include"Enemy.h"
#include"Goal.h"
#include"Map.h"
#include"Fallingfloor.h"
#include"FireTrap.h"
#include"../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Map());
	//�v���C���[�z�u
	Base::Add(new Player(CVector2D(MAP_HEIGHT * 6, MAP_WIDTH * 6), false));
	//�G�z�u
	Base::Add(new Enemy(CVector2D(1280 + 256 * 1, 540), true));
	Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//�S�[���z�u
	Base::Add(new Goal(CVector2D(MAP_HEIGHT * 30, MAP_WIDTH * 6)));
	//�����鏰�z�u
	Base::Add(new Fallingfloor(CVector2D(MAP_HEIGHT * 20, MAP_WIDTH * 6)));
	//�Β��̔z�u
	Base::Add(new FireTrap(CVector2D(MAP_HEIGHT * 20, MAP_WIDTH * 6)));




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


