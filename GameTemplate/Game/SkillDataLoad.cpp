#include "stdafx.h"
#include "SkillDataLoad.h"

SkillDataLoad* SkillDataLoad::m_instance = nullptr;

SkillDataLoad::SkillDataLoad()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;
}

SkillDataLoad::~SkillDataLoad()
{
	m_instance = nullptr;
}

void SkillDataLoad::LoadData(const char * filePath, EnSkillType type)
{
	switch (type)
	{
	case SkillDataLoad::en_Attack:
		break;
	case SkillDataLoad::en_Heal:
		break;
	case SkillDataLoad::en_Buff:
		break;
	default:
		break;
	}
}
