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
private:
	//�s���̏�ԑJ�ڂ̗񋓁B
	enum ActionState {
		en_state_Tame,
		en_state_Attack,
		en_state_Return,
		en_state_Num
	};
	ActionState m_actState = en_state_Tame;		//�s���̃X�e�[�g�B
};

