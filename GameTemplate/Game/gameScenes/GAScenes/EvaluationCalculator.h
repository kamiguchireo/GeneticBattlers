#pragma once
#include "GAScenes.h"

class SkillCalculator;
class SkillDataLoad;

typedef std::vector<MonsterData*> MonsterList;

struct MonsterInfo
{
	MonsterData* actionMonster = nullptr;
	bool IsEnemy = false;
};

/// <summary>
/// �]���l�v�Z�@
/// </summary>

class EvaluationCalculator : public IGameObject
{
public:
	EvaluationCalculator();
	~EvaluationCalculator();

	void SetEnemyAI(GA::AITable& ai, GA::Job job);

	/// <summary>
	/// �������v�Z����B
	/// </summary>
	/// <param name="table">1�̈�`�q</param>
	/// <returns>����(%)</returns>
	GA::Evaluation Calculation(GA::AITableList& table);

private:
	bool Battle();

	void ActiveTime();

	//�s�����s���B
	void Action();
	//�s�������肷��B
	void DisideSkill(int& skill, int& target);
	//�^�[�Q�b�g���X�g�쐬�B
	void SetTargetList(int skill);
	//�X�L�����g���B
	int UseSkill(const int skill,const int target);
	/// <summary>
	/// ��Ԃ��X�V����B
	/// </summary>
	/// <param name="isWin">�퓬�������H</param>
	/// <returns>�퓬���I��������ǂ����B</returns>
	bool MonsterStateUpdate(bool& isWin);


	const int LOOP_NUMBER = 20;	//��������̐퓬�񐔁B

	//MonsterList m_members;
	//MonsterList m_enemys;
	MonsterData m_members[GA::en_JobNum];
	MonsterData m_enemys[GA::en_JobNum];

	MonsterInfo monsterACT;			//���ݍs���������X�^�[�̏��B
	MonsterList m_targetList;
	std::vector<MonsterInfo> m_actionList;
	std::vector<int> m_resultValueList;			//�]���l�̉ϒ��z��B
	SkillCalculator* m_skillCalc = nullptr;
	SkillDataLoad* m_skillData = nullptr;
	int m_resultValue = 0;
};

