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
	//プレイヤー配置
	Base::Add(new Player(CVector2D(MAP_TIP_SIZE * 3, MAP_TIP_SIZE * 20), false));
	//敵配置
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 1, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//ゴール配置
	Base::Add(new Goal(CVector2D(MAP_TIP_SIZE * 9, MAP_TIP_SIZE * 18)));
	//スタート配置
	Base::Add(new Start(CVector2D(MAP_TIP_SIZE * 3, MAP_TIP_SIZE * 21)));
	//落ちる床配置
	Base::Add(new Fallingfloor(CVector2D(MAP_TIP_SIZE * 10, MAP_TIP_SIZE * 17)));
	//火柱の配置
	Base::Add(new FireTrap(CVector2D(MAP_TIP_SIZE * 12, MAP_TIP_SIZE * 17),false));




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


