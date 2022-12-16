#include "Base.h"
std::list<Base*> Base::m_list[Base::eLayer_Max];
//�X�N���[���l�̒�`
CVector2D Base::m_scroll[eLayer_Max] = { {0,0},{0,0},{0,0} };


Base::Base(int type,int layer):
	m_type(type),m_pos(0,0),m_vec(0,0), m_rad(0),m_kill(false),m_layer(layer) {

}
bool Base::CollisionRect(Base* b1, Base* b2)
{
	//b1�̒Z�`
	CRect rect1 = CRect(
		b1->m_pos.x + b1->m_rect.m_left,
		b1->m_pos.y + b1->m_rect.m_top,
		b1->m_pos.x + b1->m_rect.m_right,
		b1->m_pos.y + b1->m_rect.m_bottom);
	//b2�̒Z�`
	CRect rect2 = CRect(
		b2->m_pos.x + b2->m_rect.m_left,
		b2->m_pos.y + b2->m_rect.m_top,
		b2->m_pos.x + b2->m_rect.m_right,
		b2->m_pos.y + b2->m_rect.m_bottom);

		//�Z�`���m�̔���
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
			return true;
	
	return false;
}
void Base::DrawRect()
{
	//�f�o�b�O�p�@�Z�`�̕\��
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
	//���W�[�X�N���[���l����ʏ�ł̈ʒu
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
	//�擪�̗v�f
	auto it = m_list[layer].begin();
	//�����̗v�f
	auto last = m_list[layer].end();
	//it�������łȂ����
	while (it != last) {
		if((*it)->m_type==type){
		//�������I�u�W�F�N�g�̕ԋp
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
		//�S�ẴI�u�W�F�N�g�̍X�V
		for (auto& b : list) {
			b->Update();
		}
	}
}

void Base::DrawAll()
{
	//��ʕ\���ʒu
	const CVector2D view_pos[] = {
		{ 0,1080 / 2},		//�㔼��
		{ 0,0 },			//������
		{ 0,0 }				//�S���
	};
	//��ʕ\���T�C�Y
	CVector2D view_size[] = {
		{ 1920,1080 / 2},	//�㔼��
		{ 1920,1080 / 2},	//������
		{ 1920,1080},		//�S���
	};
	int layer = 0;
	for (auto& list : m_list) {
		//�`��̈�ݒ�
		glViewport(view_pos[layer].x, view_pos[layer].y, view_size[layer].x, view_size[layer].y);
		CCamera::GetCamera()->Viewport(view_pos[layer].x, view_pos[layer].y, view_size[layer].x, view_size[layer].y);
		//�`��𑜓x�ݒ�
		CCamera::GetCamera()->SetSize(view_size[layer].x, view_size[layer].y);
        //�S�ẴI�u�W�F�N�g�̕`�揈��
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
					//����
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
	//�I�u�W�F�N�g�̖����ɒǉ�
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
	
