#include"Title.h"
#include"../Game/GameData.h"
#include"../Game/Game.h"

Title::Title():Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("Title", CImage);
}

Title::~Title()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//ゲームシーンへ
	Base::Add(new Game());
}

void Title::Update()
{
	//ボタン1でタイトル破棄＆チュートリアルステージ
	if (PUSH(CInput::eButton1)) {
		SetKill();
		GameData::stage = 0;
		GameData::s_count = 0;
		GameData::s_kosu = 5;
	}
	//ボタン3でタイトル破棄＆ステージ１
	if (PUSH(CInput::eButton3)) {
		SetKill();
		GameData::stage = 1;
		GameData::s_count = 0;
		GameData::s_kosu = 5;
	}
}

void Title::Draw()
{
	m_img.Draw();
	//文字表示
	m_title_text.Draw(64, 256, 0, 0, 0, "Title");
	m_title_text.Draw(64, 512, 0, 0, 0, "Push W");
	m_title_text.Draw(64, 560, 0, 0, 0, "Push S");
}
