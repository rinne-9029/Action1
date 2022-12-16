#include "Base.h"
std::list<Base*> Base::m_list[Base::eLayer_Max];
//スクロール値の定義
CVector2D Base::m_scroll[eLayer_Max] = { {0,0},{0,0},{0,0} };


Base::Base(int type,int layer):
	m_type(type),m_pos(0,0),m_vec(0,0), m_rad(0),m_kill(false),m_layer(layer) {

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
		CVector2D(rect.m_left, rect.m_top) - m_scroll[m_layer],
		CVector2D(rect.m_width, rect.m_height),
		CVector4D(1, 0, 0, 0.5f)
	);
}
CVector2D Base::GetScreenPos(const CVector2D& pos) {
	//座標ースクロール値＝画面上での位置
	return pos - m_scroll[m_layer];
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
Base* Base::FindObject(int type,int layer)
{
	//先頭の要素
	auto it = m_list[layer].begin();
	//末尾の要素
	auto last = m_list[layer].end();
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
	for (auto& list : m_list) {
		//全てのオブジェクトの更新
		for (auto& b : list) {
			b->Update();
		}
	}
}

void Base::DrawAll()
{
	//画面表示位置
	const CVector2D view_pos[] = {
		{ 0,1080 / 2},		//上半分
		{ 0,0 },			//下半分
		{ 0,0 }				//全画面
	};
	//画面表示サイズ
	CVector2D view_size[] = {
		{ 1920,1080 / 2},	//上半分
		{ 1920,1080 / 2},	//下半分
		{ 1920,1080},		//全画面
	};
	int layer = 0;
	for (auto& list : m_list) {
		//描画領域設定
		glViewport(view_pos[layer].x, view_pos[layer].y, view_size[layer].x, view_size[layer].y);
		CCamera::GetCamera()->Viewport(view_pos[layer].x, view_pos[layer].y, view_size[layer].x, view_size[layer].y);
		//描画解像度設定
		CCamera::GetCamera()->SetSize(view_size[layer].x, view_size[layer].y);
        //全てのオブジェクトの描画処理
	    for (auto& b : list) {
			b->Draw();
	}
		layer++;
	}	
}

void Base::CollisionAll()
{
	for (auto& list : m_list) {
		auto it1 = list.begin();
		auto last = list.end();
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
}
void Base::CheckKillAll()
{
	for (auto& list : m_list) {
		auto it = list.begin();
			auto last = list.end();
			while (it != last) {
				if ((*it)->m_kill) {
					delete(*it);
					it = list.erase(it);
				}
				else {
					//次へ
					it++;
			}
		}
	}	
}
void Base::Add(Base* b)
{
	//
	auto itr = m_list[b->m_layer].begin();
	while (itr != m_list[b->m_layer].end()) {
		if ((*itr)->m_type > b->m_type) {
			m_list[b->m_layer].insert(itr, b);
			return;
		}
		itr++;
	}
	//オブジェクトの末尾に追加
	m_list[b->m_layer].push_back(b);
}

void Base::KillAll()
{
	for (auto& list : m_list) {
		for (auto& b : list) {
			b->SetKill();
		}
	}
}
	
