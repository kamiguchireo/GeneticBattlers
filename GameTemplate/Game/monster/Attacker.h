#pragma once
#include "MonsterBase.h"
class Attacker :public MonsterBase
{
public:
	Attacker();
	~Attacker();

	bool Start();
	void Update();
	bool BattleAction();
	//スキル選択。
	void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team) override;
	//AIデータを読み込みたい。
	void Init(const wchar_t* filePath);

private:
	//enum enAnimation {
	//	en_anim_Idle,
	//	en_anim_Attack,
	//	en_anim_Damage,
	//	en_anim_num
	//};
	//Animation m_animation;
	//AnimationClip m_animClip[en_anim_num];
};

