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

bool SkillDataLoad::Start()
{


	return true;
}

SkillData SkillDataLoad::GetSkillData(int No)
{
	//スキルのタイプ、番号を調べる
	int typeNum = int(No / 100);
	int skillNo = No % 100;
	SkillData retData;
	switch (typeNum)
	{
	case SkillDataLoad::en_Attack:
		retData = m_attackSkillList[skillNo];
		break;
	case SkillDataLoad::en_Heal:
		retData = m_healSkillList[skillNo];
		break;
	case SkillDataLoad::en_Buff:
		retData = m_buffSkillList[skillNo];
		break;
	default:
		break;
	}
	return retData;
}

void SkillDataLoad::LoadData(const char * FilePath, EnSkillType skillType)
{
	SkillDataList* SList;
	switch (skillType)
	{
	case SkillDataLoad::en_Attack:
		SList = &m_attackSkillList;
		break;
	case SkillDataLoad::en_Heal:
		SList = &m_healSkillList;
		break;
	case SkillDataLoad::en_Buff:
		SList = &m_buffSkillList;
		break;
	default:
		return;
		break;
	}

	FILE* fp = fopen(FilePath, "r");
	if (fp == nullptr) return;

	char text[256];
	while (fgets(text, 256, fp) != NULL)
	{
		SkillData loadData;
		wchar_t skillName[64];
		char nextNoBuffer[128];
		sscanf(text, "%[^,] ,%f,%f,%f,%d,%s",
			skillName,
			loadData.Power,
			loadData.CoolTime,
			loadData.HitRate,
			loadData.SkillNo,
			nextNoBuffer
		);
		loadData.Name = skillName;

		int nextNo = 0;
		while (sscanf(nextNoBuffer,"%d", nextNo)!=EOF)
		{
			loadData.NextSkillNo.push_back(nextNo);
		}


		SList->push_back(loadData);
	}

	fclose(fp);
}

