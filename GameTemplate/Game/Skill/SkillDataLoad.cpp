#include "stdafx.h"
#include "SkillDataLoad.h"

static const int NOSKILL = -1;
static const int MAX_NEXT_SIZE = 3;

SkillDataLoad* SkillDataLoad::m_instance = nullptr;

SkillDataLoad::SkillDataLoad()
{
	//�C���X�^���X�������ԂŐ������ꂽ�炷���폜
	if (m_instance != nullptr)
	{
		DeleteGO(this);
	}
	else {
		m_instance = this;
	}
}

SkillDataLoad::~SkillDataLoad()
{
	if (this == m_instance)
	{
		m_instance = nullptr;
	}
}

bool SkillDataLoad::Start()
{


	return true;
}

SkillData SkillDataLoad::GetSkillData(int No)
{
	//�X�L���̃^�C�v�A�ԍ��𒲂ׂ�
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
		//�X�L���f�[�^�ǂݍ���
		SkillData loadData;
		char skillName[64];
		char nextNoBuffer[128];
		sscanf(text, "%[^,],%f,%f,%f,%d,%s",
			skillName,				//���O�B
			&loadData.Power,		//�З́B
			&loadData.CoolTime,		//�N�[���^�C���B
			&loadData.HitRate,		//�������B
			&loadData.SkillNo,		//�X�L���ԍ�
			nextNoBuffer			//���̃X�L���ԍ��B
		);
		//�X�L���������C�h�^������ɂ���B
		wchar_t buffer[64];
		mbstowcs(buffer, skillName, sizeof(skillName));
		loadData.Name = buffer;

		//���̃X�L���ԍ���o�^�������ǂݍ���(�����悭�Ȃ�)
		int nextNo[MAX_NEXT_SIZE] = { NOSKILL,NOSKILL,NOSKILL };
		sscanf(nextNoBuffer, "%d,%d,%d", &nextNo[0], &nextNo[1], &nextNo[2]);
		for (int i = 0; i < MAX_NEXT_SIZE; i++)
		{
			if (nextNo[i] != NOSKILL)
			{
				loadData.NextSkillNo.push_back(nextNo[i]);
			}
		}

		//�X�L���f�[�^�����X�g�ɐςݍ��ށB
		SList->push_back(loadData);
	}

	fclose(fp);
}

