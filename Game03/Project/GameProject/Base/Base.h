#pragma once
#include<GLLibrary.h>
//重力加速度
#define GRAVITY (9.8f/20)
enum {
	eType_Field,
	eType_Goal,
	eType_Start,
	eType_Signboard,
	eType_Spike,
	eType_Item,
    eType_Player,
	eType_Enemy,
	eType_FireTrap,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
    eType_UI,
	eType_UI2,
	eType_Scene,
	eType_Fallingfloor,
};



class Base {
public:
	enum {
		eLayer_Top,
		eLayer_Bottom,
		eLayer_Default,
		eLayer_Max
	};
	//オブジェクトのレイヤー
	int m_layer;
	//オブジェクトの種類
	int m_type;
	//座標データ
	CVector2D m_pos; 
	CVector2D m_pos_old;
	//半径
	float m_rad;
	//移動ベクトル
	CVector2D m_vec;
	//スクロール値
	static CVector2D m_scroll[eLayer_Max];
	//削除フラグ
	bool m_kill;
	//オブジェクトのリスト
	static std::list<Base*>m_list[eLayer_Max];
	//短形
	CRect m_rect;

public:
	//typeオブジェクトの種類
	Base(int type,int layer = eLayer_Default); //コンストラクタ
	virtual~Base(); //デストラクタ
	virtual void Update(); //更新処理
	virtual void Draw(); //描画処理
	virtual void Collision(Base* b);
	//削除フラグON
	void SetKill() { m_kill = true; }
	//短形同士の判定
	static bool CollisionRect(Base* b1, Base* b2);
	//短形の表示
	void DrawRect();

	CVector2D GetScreenPos(const CVector2D& pos);
	//全てのオブジェクトの更新
	static void UpdateAll();
	//全てのオブジェクトの描画
	static void DrawAll();
	//全てのオブジェクトの当たり判定検証
	   static void CollisionAll();
	   //削除チェック
	   static void CheckKillAll();
	//オブジェクトの追加
 static void Add(Base* b);
 //全オブジェクトの削除
 static void KillAll();
 //円同士の衝突
 static bool CollisionCircle(Base* b1, Base* b2);
 Base* Base::FindObject(int type, int layer = eLayer_Default);
};