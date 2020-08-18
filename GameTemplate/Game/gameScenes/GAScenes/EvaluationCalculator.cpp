#include "stdafx.h"
#include "EvaluationCalculator.h"
#include "Skill/SkillCalculator.h"
#include "Skill/SkillDataLoad.h"

using namespace GA;

EvaluationCalculator::EvaluationCalculator()
{
	//�����̃X�e�[�^�X�ݒ�B
	m_members[en_Attacker].GetStatusManager()->StatusAttaker();
	m_members[en_Healer].GetStatusManager()->StatusHealer();
	m_members[en_Supporter].GetStatusManager()->StatusSupporter();
	//�G�̃X�e�[�^�X�ݒ�B
	m_enemys[en_Attacker].GetStatusManager()->StatusAttaker();
	m_enemys[en_Healer].GetStatusManager()->StatusHealer();
	m_enemys[en_Supporter].GetStatusManager()->StatusSupporter();
	//�X�L���v�Z�@�̎��̉��B
	m_skillCalc = new SkillCalculator();

	m_skillData = SkillDataLoad::GetInstance();
	if (m_skillData == nullptr)
	{
		m_skillData = NewGO<SkillDataLoad>(0);
	}
}

EvaluationCalculator::~EvaluationCalculator()
{
	if (m_skillCalc != nullptr)
	{
		delete m_skillCalc;
	}
	DeleteGO(m_skillData);
}

int EvaluationCalculator::Calculation(AITableList & table)
{
	//AI���Z�b�g�B
	m_members[en_Attacker].GetAIManager().SetAIData(table[en_Attacker]);
	m_members[en_Healer].GetAIManager().SetAIData(table[en_Healer]);
	m_members[en_Supporter].GetAIManager().SetAIData(table[en_Supporter]);

	int winCount = 0;

	for (int i = 0; i < LOOP_NUMBER; i++)
	{
		//�X�e�[�^�X�����ɖ߂��Ă����B
		for (auto& data : m_members)
		{
			data.GetStatusManager()->ResetStatus();
		}
		for (auto& data : m_enemys)
		{
			data.GetStatusManager()->ResetStatus();
		}
		//�퓬�ɏ����������H
		if (Battle())
		{
			winCount++;
		}
	}

	return winCount;
}

bool EvaluationCalculator::Battle()
{
	bool battleFlag = false;
	bool IsWin = false;
	while (!battleFlag)
	{
		//�s�����Ă���B
		if (m_actionList.size() > 0)
		{
			Action();
			battleFlag = MonsterStateUpdate(IsWin);
		}
		else	//�s�����Ă��Ȃ��B
		{
			ActiveTime();
		}
	}

	return IsWin;
}

void EvaluationCalculator::ActiveTime()
{
	//�����̍X�V�B
	for (auto& data : m_members)
	{
		if (data.GetStatusManager()->AddATB())
		{
			m_actionList.push_back({ &data,false });
		}
	}
	//�G���̍X�V�B
	for (auto& data : m_enemys)
	{
		if (data.GetStatusManager()->AddATB())
		{
			m_actionList.push_back({ &data,true });
		}
	}
}

void EvaluationCalculator::Action()
{
	if (m_skillData == nullptr)
	{
		m_skillData = SkillDataLoad::GetInstance();
	}

	monsterACT = m_actionList.front();

	//�s���҂����S���Ă���B
	if (monsterACT.actionMonster->GetStatusManager()->IsDeath())
	{
		m_actionList.erase(m_actionList.begin());
		monsterACT = { nullptr,false };		//�������B

		return;
	}

	//SortTeams();

	int skill, target;
	//�s������̏����B
	DisideSkill(skill, target);

	//�^�[�Q�b�g���X�g�쐬�B
	SetTargetList(skill);

	//�X�L�����g�p����B
	SkillData sData = m_skillData->GetSkillData(skill);
	//�S�̌��ʂ̃X�L�����H
	if (sData.targetNum == en_JobNum)
	{
		//�S�̂ɑ΂��Ďg�p�B
		for (auto& data : m_targetList)
		{
			m_skillCalc->SkillCalculation(
				monsterACT.actionMonster->GetStatusManager(),
				data->GetStatusManager(),
				skill
			);
		}
	}
	else
	{
		//�^�[�Q�b�g�ɑ΂��Ďg�p�B
		m_skillCalc->SkillCalculation(
			monsterACT.actionMonster->GetStatusManager(),
			m_targetList[target]->GetStatusManager(),
			skill
		);
	}

	//�s���I���B
	m_actionList.erase(m_actionList.begin());
	monsterACT = { nullptr,false };		//�������B
}

void EvaluationCalculator::DisideSkill(int& skill,int& target)
{
	bool ActionFlag = true;

	while (ActionFlag)
	{
		//�s���̌���B
		monsterACT.actionMonster->GetAIManager().ActionDicide(skill, target);
		//�^�[�Q�b�g�̎��S�m�F�B
		if (monsterACT.IsEnemy) {		//�G�̍s���I���B
			if (m_skillData->IsAttackSkill(skill)) {
				ActionFlag = m_members[target].GetStatusManager()->IsDeath();
			}
			else {
				ActionFlag = m_enemys[target].GetStatusManager()->IsDeath();
			}
		}
		else {							//�����̍s���I���B
			if (m_skillData->IsAttackSkill(skill)) {
				ActionFlag = m_enemys[target].GetStatusManager()->IsDeath();
			}
			else {
				ActionFlag = m_members[target].GetStatusManager()->IsDeath();
			}
		}
	}
}

void EvaluationCalculator::SetTargetList(int skill)
{
	//�z������Z�b�g�B
	m_targetList.clear();
	m_targetList.resize(en_JobNum);

	MonsterList memberList;		//�s���҂̃`�[���B
	memberList.resize(en_JobNum);
	MonsterList enemyList;		//�s���҂̓G�΃`�[���B
	enemyList.resize(en_JobNum);

	//�^�[�Q�b�g���X�g�쐬�B
	if (monsterACT.IsEnemy)		//�s���҂��G�B
	{
		//�������X�g�쐬�B
		memberList[en_Attacker] = &m_enemys[en_Attacker];
		memberList[en_Healer] = &m_enemys[en_Healer];
		memberList[en_Supporter] = &m_enemys[en_Supporter];
		//�G�Ύ҂̃��X�g�B
		enemyList[en_Attacker] = &m_members[en_Attacker];
		enemyList[en_Healer] = &m_members[en_Healer];
		enemyList[en_Supporter] = &m_members[en_Supporter];
		
	}
	else		//�s���҂������B
	{
		//�������X�g�쐬�B
		memberList[en_Attacker] = &m_members[en_Attacker];
		memberList[en_Healer] = &m_members[en_Healer];
		memberList[en_Supporter] = &m_members[en_Supporter];
		//�G�Ύ҂̃��X�g�B
		enemyList[en_Attacker] = &m_enemys[en_Attacker];
		enemyList[en_Healer] = &m_enemys[en_Healer];
		enemyList[en_Supporter] = &m_enemys[en_Supporter];
	}
	if (m_skillData->IsAttackSkill(skill))
	{
		//�G���̃��X�g�쐬�B
		m_targetList = enemyList;
	}
	else
	{
		//�����̃��X�g�쐬�B
		m_targetList = memberList;
	}
}

bool EvaluationCalculator::MonsterStateUpdate(bool& isWin)
{
	int mDeathNum = 0;
	int eDeathNum = 0;

	//��ԍX�V�Ɛ퓬�I�����ǂ�������B
	for (auto& data : m_members)
	{
		//��ԍX�V�B
		data.GetStatusManager()->StateUpdate();
		if (data.GetStatusManager()->IsDeath())
		{
			//���S�����J�E���g�B
			mDeathNum++;
		}
	}
	//�S�ł��Ă���Ȃ�I���B
	if (mDeathNum == en_JobNum)
	{
		isWin = false;
		return true;
	}
	for (auto& data : m_enemys)
	{
		//��ԍX�V�B
		data.GetStatusManager()->StateUpdate();
		if (data.GetStatusManager()->IsDeath())
		{
			//���S�����J�E���g�B
			eDeathNum++;
		}
	}
	//�S�ł��Ă���Ȃ�퓬�I���B
	if (eDeathNum == en_JobNum)
	{
		isWin = true;
		return true;
	}

	return false;
}
