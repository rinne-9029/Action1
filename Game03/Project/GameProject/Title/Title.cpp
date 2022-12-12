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
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�Q�[���V�[����
	Base::Add(new Game());
}

void Title::Update()
{
	//�{�^��1�Ń^�C�g���j�����`���[�g���A���X�e�[�W
	if (PUSH(CInput::eButton1)) {
		SetKill();
		GameData::stage = 0;
		GameData::s_count = 0;
		GameData::s_kosu = 5;
	}
	//�{�^��3�Ń^�C�g���j�����X�e�[�W�P
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
	//�����\��
	m_title_text.Draw(64, 256, 0, 0, 0, "Title");
	m_title_text.Draw(64, 512, 0, 0, 0, "Push W");
	m_title_text.Draw(64, 560, 0, 0, 0, "Push S");
}
