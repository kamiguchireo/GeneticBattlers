#pragma once
#include "monster/MonsterBase.h"
#include "Skill/SkillList.h"

class MonsterTeam1 : public MonsterBase
{
public:
	MonsterTeam1();
	~MonsterTeam1();
	bool Start();

	bool ACTScoring() 
	{
		m_status.ClearATB();
		m_UI->SetScaling(0.0f);
		DeleteGO("sLog");
		return true; 
	};

private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/DefaultData/EnemyData.bin";		//�l�b�g�ł͂Ȃ��Ƃ���AI�B
	}

	//�s���̏�ԑJ�ڂ̗񋓁B
	enum ActionState {
		en_state_Tame,
		en_state_Attack,
		en_state_Return,
		en_state_Num
	};

};

