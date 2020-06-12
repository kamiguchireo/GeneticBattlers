#pragma once
#include "monster/MonsterBase.h"
#include "Skill/SkillList.h"

class MonsterTeam1 : public MonsterBase
{
public:
	MonsterTeam1();
	~MonsterTeam1();
	bool Start();
	void Update();

	bool ACTScoring() { return true; };
	//AI�f�[�^��ǂݍ��݂����B
	void Init(const char* filePath)override 
	{
		//�f�t�H���g�̃f�[�^�̃t�@�C����ǂݍ��ށB
		m_GIData.LoadDefault(GetDefaultDataPath());
	};

	void SetUIPos(const CVector3& pos)
	{
		m_UIpos = pos;
	}

private:
	const char* GetDefaultDataPath()
	{
		//return "Assets/AIData/HealerDefault.bin";
		return "Assets/AIData/Healer.bin";		//���u���s���B
	}

	//�s���̏�ԑJ�ڂ̗񋓁B
	enum ActionState {
		en_state_Tame,
		en_state_Attack,
		en_state_Return,
		en_state_Num
	};

	CVector3 m_UIpos = CVector3::Zero();
};

