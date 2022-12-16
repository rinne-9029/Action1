#include"Game.h"
#include"GameData.h"
#include"Map.h"
#include"UI.h"
#include"../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	int player_size =2;
	if (player_size == 1) {
		//ステージごとのマップチップを読み込む処理
		Base::Add(new Map(GameData::stage, 0, Base::eLayer_Default));
		//時間を読み込む処理
		Base::Add(new UI(Base::eLayer_Default));
		//HPを読み込む処理
		Base::Add(new UI2(Base::eLayer_Default));
	}else {
		//ステージごとのマップチップを読み込む処理
		Base::Add(new Map(GameData::stage, 0, Base::eLayer_Top));
		//時間を読み込む処理
		Base::Add(new UI(Base::eLayer_Top));
		//HPを読み込む処理
		Base::Add(new UI2(Base::eLayer_Top));


		//ステージごとのマップチップを読み込む処理
		Base::Add(new Map(GameData::stage, 1, Base::eLayer_Bottom));
		//時間を読み込む処理
		Base::Add(new UI(Base::eLayer_Bottom));
		//HPを読み込む処理
		Base::Add(new UI2(Base::eLayer_Bottom));
	}
	
	
	

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
	if (!Base::FindObject(eType_Goal,Base::eLayer_Top)) {
		SetKill();
	}
	//プレイヤー1P死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player,Base::eLayer_Top ) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}


