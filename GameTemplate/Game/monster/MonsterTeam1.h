#pragma once
#include "monster/MonsterBase.h"

class MonsterTeam1 : public MonsterBase
{
public:
	MonsterTeam1();
	~MonsterTeam1();
	bool Start();
	void Update();
	bool Action_good();
	bool Action_usually();
	bool Action_bad();
	bool BattleAction();
	bool ACTScoring() { return true; };

	void SetUIPos(const CVector3& pos)
	{
		m_UIpos = pos;
	}
private:
	//�s���̏�ԑJ�ڂ̗񋓁B
	enum ActionState {
		en_state_Tame,
		en_state_Attack,
		en_state_Return,
		en_state_Num
	};

	CVector3 m_UIpos = CVector3::Zero();

	////�A�j���[�V�����̗񋓁B
	//enum enAnimation {
	//	en_anim_Idle,
	//	en_anim_Attack,
	//	en_anim_Damage,
	//	en_anim_Death,
	//	en_anim_num
	//};
	//Animation m_animation;								//�A�j���[�V�����B
	//AnimationClip m_animClip[en_anim_num];				//�A�j���[�V�����N���b�v�B
};

