#pragma once
#include "../engine/GameEngine.h"

class GameObject {

public:
	GameObject();
	virtual ~GameObject();

protected:
	// ---- メンバ変数 ---- //
	std::string m_name = "";					//名前
	int m_draw_order = 0;						//描画順番
	bool m_is_exist = true;						//存在フラグ
	bool m_is_update = true;					//更新フラグ
	bool m_is_draw = true;						//描画フラグ
	tnl::Vector3 m_pos = { 0, 0, 0 };			//座標
	eCharaType e_chara_type = eCharaType::Max;	//キャラタイプ判定用

public:
	//-----メンバ関数-----//
	virtual void Initialize() {}
	virtual void Update(float delta_time) { Finalize(); }
	virtual void Draw() {}
	virtual void Finalize() {}

public:
	//-----Setter&Getter-----//
	std::string GetName() const { return m_name; }
	
	eCharaType GetTag() const { return e_chara_type; }
	void SetTag(eCharaType charaType) { e_chara_type = charaType; }
	
	int GetDrawOrder() const { return m_draw_order; }
	
	bool GetIsExist() const { return m_is_exist; }
	void SetIsExist(bool is_exist) { m_is_exist = is_exist; }
	
	bool GetIsUpdate() const { return m_is_update; }
	void SetIsUpdate(bool is_update) { m_is_update = is_update; }
	
	bool GetIsDraw() const { return m_is_draw; }
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }
	
	tnl::Vector3 GetPos() const { return m_pos; }
	void SetPos(tnl::Vector3 pos) { m_pos = pos; }
};