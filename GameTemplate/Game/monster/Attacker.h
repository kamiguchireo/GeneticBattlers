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
	void SelectUseSkill(const std::vector<MonsterBase*>& enemylist, const std::vector<MonsterBase*>& allylist) override;

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

