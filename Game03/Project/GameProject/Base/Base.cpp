#include "Base.h"
std::list<Base*> Base::m_list;
//スクロール値の定義
CVector2D Base::m_scroll(0, 0);


Base::Base(int type):m_type(type),m_pos(0,0),m_vec(0,0), m_rad(0),m_kill(false) {

}
bool Base::CollisionRect(Base* b1, Base* b2)
{
	//b1の短形
	CRect rect1 = CRect(
		b1->m_pos.x + b1->m_rect.m_left,
		b1->m_pos.y + b1->m_rect.m_top,
		b1->m_pos.x + b1->m_rect.m_right,
		b1->m_pos.y + b1->m_rect.m_bottom);
	//b2の短形
	CRect rect2 = CRect(
		b2->m_pos.x + b2->m_rect.m_left,
		b2->m_pos.y + b2->m_rect.m_top,
		b2->m_pos.x + b2->m_rect.m_right,
		b2->m_pos.y + b2->m_rect.m_bottom);

		//短形同士の判定
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
			return true;
	
	return false;
}
void Base::DrawRect()
{
	//デバッグ用　短形の表示
	CRect rect = CRect(
		m_pos.x + m_rect.m_left,
		m_pos.y + m_rect.m_top,
		m_pos.x + m_rect.m_right,
		m_pos.y + m_rect.m_bottom
	);
	Utility::DrawQuad(
		CVector2D(rect.m_left, rect.m_top) - m_scroll,
		CVector2D(rect.m_width, rect.m_height),
		CVector4D(1, 0, 0, 0.5f)
	);
}
CVector2D Base::GetScreenPos(const CVector2D& pos) {
	//座標ースクロール値＝画面上での位置
	return pos - m_scroll;
}

bool Base::CollisionCircle(Base* b1, Base* b2)
{
	CVector2D v = b1->m_pos - b2->m_pos;
	float l = v.Length();
	if (l < b1->m_rad + b2->m_rad) {
		return true;
	}
	return false;
}
Base* Base::FindObject(int type)
{
	//先頭の要素
	auto it = m_list.begin();
	//末尾の要素
	auto last = m_list.end();
	//itが末尾でなければ
	while (it != last) {
		if((*it)->m_type==type){
		//見つけたオブジェクトの返却
		return(*it);
	}
	it++;
}
	return nullptr;
}
Base::~Base() {

}
void Base::Update() {
	
}
void Base::Collision(Base* b)
{

}
void Base::Draw() {

}
void Base::UpdateAll()
{
	//全てのオブジェクトの更新
for (auto& b : m_list) {
		b->Update();
	}
}

void Base::DrawAll()
{
	//全てのオブジェクトの描画処理
	for (auto& b : m_list) {
		b->Draw();
	}
	
}

void Base::CollisionAll()
{
	auto it1 = m_list.begin();
	auto last = m_list.end();
	while (it1 != last) {
		auto it2 = it1;
		it2++;
		while (it2 != last) {
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			it2++;
		}
		it1++;
	}
}
void Base::CheckKillAll()
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_kill) {
			delete(*it);
			it = m_list.erase(it);
		}
		else {
			//次へ
			it++;
		}
	}
}
void Base::Add(Base* b)
{
	//
	auto itr = m_list.begin();
	while (itr != m_list.end()) {
		if ((*itr)->m_type > b->m_type) {
			m_list.insert(itr, b);
			return;
		}
		itr++;
	}
	//オブジェクトの末尾に追加
	m_list.push_back(b);
}

void Base::KillAll()
{
	std::list<Base*>ret;
	for (auto& b : m_list) {
		b->SetKill();
	}
}
