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
	//プレイヤー配置
	Base::Add(new Player(CVector2D(MAP_HEIGHT * 6, MAP_WIDTH * 6), false));
	//敵配置
	Base::Add(new Enemy(CVector2D(1280 + 256 * 1, 540), true));
	Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//ゴール配置
	Base::Add(new Goal(CVector2D(MAP_HEIGHT * 30, MAP_WIDTH * 6)));
	//落ちる床配置
	Base::Add(new Fallingfloor(CVector2D(MAP_HEIGHT * 20, MAP_WIDTH * 6)));
	//火柱の配置
	Base::Add(new FireTrap(CVector2D(MAP_HEIGHT * 20, MAP_WIDTH * 6)));




}
Game::~Game()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());
}

void Game::Update()
{
	//ゴールが無ければゲームシーン終了
	if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}
	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}


