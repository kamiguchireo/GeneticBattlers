#pragma once
#include "GAScenes.h"

class SkillCalculator;
class SkillDataLoad;

typedef std::vector<MonsterData> MonsterList;

/// <summary>
/// �]���l�v�Z�@
/// </summary>

class EvaluationCalculator
{
public:
	EvaluationCalculator();
	~EvaluationCalculator();

private:
	MonsterList m_members;
	MonsterList m_enemys;

};

