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
	//ステージごとのマップチップを読み込む処理
	Base::Add(new Map(GameData::stage));
	//時間を読み込む処理
	Base::Add(new UI());
	//HPを読み込む処理
	Base::Add(new UI2());

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


