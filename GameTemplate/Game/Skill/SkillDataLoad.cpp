#include "stdafx.h"
#include "SkillDataLoad.h"
#include "monster/parameter/StatusBase.h"

static const int MAX_NEXT_SIZE = 3;		//���̃X�L���̃T�C�Y�B

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
	LoadData("Assets/SkillData/AttackSkill.csv",en_Attack);
	LoadData("Assets/SkillData/HealSkill.csv", en_Heal);
	LoadData("Assets/SkillData/BuffSkill.csv", en_Buff);
	LoadData("Assets/SkillData/DebuffSkill.csv", en_Debuff);

	return true;
}

SkillData SkillDataLoad::GetSkillAttack(int No)
{
	if (No < m_attackSkillList.size())
	{
		return m_attackSkillList[No];
	}
	SkillData errorData;
	errorData.Name = L"�G���[�X�L��";

	return errorData;
}

SkillData SkillDataLoad::GetSkillHeal(int No)
{
	if (No < m_healSkillList.size())
	{
		return m_healSkillList[No];
	}
	SkillData errorData;
	errorData.Name = L"�G���[�X�L��";

	return errorData;
}

SkillData SkillDataLoad::GetSkillBuff(int No)
{
	if (No < m_buffSkillList.size())
	{
		return m_buffSkillList[No];
	}
	SkillData errorData;
	errorData.Name = L"�G���[�X�L��";

	return errorData;
}

SkillData SkillDataLoad::GetSkillDebuff(int No)
{
	if (No < m_debuffSkillList.size())
	{
		return m_debuffSkillList[No];
	}
	SkillData errorData;
	errorData.Name = L"�G���[�X�L��";

	return errorData;
}

SkillData SkillDataLoad::GetSkillData(int No)
{
	//�X�L���̃^�C�v�A�ԍ��𒲂ׂ�
	int typeNum = int(No / 100);
	int skillNo = No % 100;
	SkillData retData;
	switch (typeNum)
	{
	case en_Attack:
		retData = GetSkillAttack(skillNo);
		break;
	case en_Heal:
		retData = GetSkillHeal(skillNo);
		break;
	case en_Buff:
		retData = GetSkillBuff(skillNo);;
		break;
	case en_Debuff:
		retData = GetSkillDebuff(skillNo);
		break;
	default:
		retData.Name = L"�G���[�X�L��";
		break;
	}
	return retData;
}

bool SkillDataLoad::IsAttackSkill(int No)
{
	No /= 100;
	switch (No)
	{
	case en_Attack:		//�U���X�L���B
		return true;
		break;
	case en_Heal:		//�q�[���X�L���B
		return false;
		break;
	case en_Buff:		//�o�t�X�L���B
		return false;
		break;
	case en_Debuff:		//�f�o�t�X�L���B
		return true;
		break;
	default:
		break;
	}
	return false;
}

void SkillDataLoad::LoadData(const char * FilePath, EnSkillType skillType)
{
	SkillDataList* SList;
	switch (skillType)
	{
	case en_Attack:
		SList = &m_attackSkillList;
		break;
	case en_Heal:
		SList = &m_healSkillList;
		break;
	case en_Buff:
		SList = &m_buffSkillList;
		break;
	case en_Debuff:
		SList = &m_debuffSkillList;
		break;
	default:
		return;
		break;
	}

	FILE* fp = fopen(FilePath, "r");
	if (fp == nullptr) {
		//�ǂݍ��ݎ��s�B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "csv�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B%s\n", FilePath);
		OutputDebugStringA(message);
#endif		
		return;
	}
	char text[256];
	while (fgets(text, 256, fp) != NULL)
	{
		//�X�L���f�[�^�ǂݍ���
		SkillData loadData;
		char skillName[64];
		char nextNoBuffer[128];
		int StatusType = 0;
		sscanf(text, "%[^,],%f,%d,%f,%f,%d,%d,%d,%s",
			skillName,				//���O�B
			&loadData.Power,		//�З́B
			&loadData.useMP,			//����MP
			&loadData.CoolTime,		//�N�[���^�C���B
			&loadData.HitRate,		//�������B
			&loadData.targetNum,	//�U���Ώې��B
			&StatusType,			//�X�e�[�^�X�ω��B
			&loadData.SkillNo,		//�X�L���ԍ�
			nextNoBuffer			//���̃X�L���ԍ��B
		);
		//�X�e�[�^�X�ω��B
		switch (StatusType)
		{
		case en_buff_ATK:
			loadData.StatusChange = en_buff_ATK;
			break;
		case en_buff_DEF:
			loadData.StatusChange = en_buff_DEF;
			break;
		case en_buff_MAT:
			loadData.StatusChange = en_buff_MAT;
			break;
		case en_buff_MDF:
			loadData.StatusChange = en_buff_MDF;
			break;
		case en_buff_DEX:
			loadData.StatusChange = en_buff_DEX;
			break;
		case -1:
			loadData.StatusChange = en_buff_NONE;
			break;
		default:
			break;
		}

		//�X�L���������C�h�^������ɂ���B�v���Ă����������h�C�������Ȃ�
		int in_length = static_cast<int>(strlen(skillName));
		int out_length = MultiByteToWideChar(CP_ACP, 0 , skillName, in_length, 0, 0);  
		std::vector<wchar_t> buffer(out_length);
		if (out_length) {
			MultiByteToWideChar(CP_ACP, 0, skillName, in_length, &buffer[0], out_length);
		}
		std::wstring result(buffer.begin(), buffer.end());
		loadData.Name = result;

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

