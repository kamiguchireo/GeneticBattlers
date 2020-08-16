#include "stdafx.h"
#include "GAScenes.h"
#include "../BattleScenes/AIResouce.h"

const float GAScenes::RATE_CHANGE = 0.01f;	//������`�q�����̂��߂̊m���ϓ����B
const int GAScenes::CHANGE_NUM = 5;	//�m���ϓ��ō�鐔�B

GAScenes::GAScenes()
{
	//�f�[�^�ǂݍ��݁B
	LoadAIData("Assets/AIData/Attacker.bin", m_myAI[en_Attacker]);
	LoadAIData("Assets/AIData/Healer.bin", m_myAI[en_Healer]);
	LoadAIData("Assets/AIData/Supporter.bin", m_myAI[en_Supporter]);

	auto aiResouce = AIResouce::GetInstance();
	if (aiResouce != nullptr)
	{
		m_enemyAI[en_Attacker] = aiResouce->GetAttacker();
		m_enemyAI[en_Healer] = aiResouce->GetHealer();
		m_enemyAI[en_Supporter] = aiResouce->GetSupporter();
		DeleteGO(aiResouce);
	}
}

GAScenes::~GAScenes()
{
}

bool GAScenes::Start()
{
	//�s���̐����L�^�B
	m_actionNum = 0;
	for (auto& ai : m_myAI)
	{
		m_actionNum += ai.size();
	}
	//������`�q����������쐬�B
	FirstGenesCreate();

	return true;
}

void GAScenes::Update()
{
}

void GAScenes::LoadAIData(const char * filePath, AITable & ai)
{
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//�ǂݍ��ݎ��s�B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "bin�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B%s\n", filePath);
		OutputDebugStringA(message);
#endif
		return;
	}

	//�ǂݍ���ł����B
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		ai.push_back(hoge);
	}

	fclose(fp);
}

void GAScenes::FirstGenesCreate()
{
	//����AI���R�s�[
	AITableList tables;
	tables.resize(en_JobNum);
	tables[en_Attacker] = m_myAI[en_Attacker];
	tables[en_Healer] = m_myAI[en_Healer];
	tables[en_Supporter] = m_myAI[en_Supporter];

	//�m���ϓ��̂Ȃ��f�[�^���L�^�B
	m_currentGenetics.push_back(tables);
	//��`�q�̐����s���̐��}5%�̐��܂ő��₷�B
	for (auto& job: tables)		//�W���u���ɉ񂷁B
	{
		for (int i = 0; i < job.size(); i++)
		{
			//�ϓ������錳�̊m��������Ă����B
			float rate = job[i].rate;

			for (int j = 0; j < CHANGE_NUM; j++)
			{
				//�m����+�ɕϓ�������B
				job[i].rate = rate + RATE_CHANGE * (j + 1);

				//���s��`�q�ɋL�^����B
				m_currentGenetics.push_back(tables);

				//�m����-�ɕϓ�������B
				job[i].rate = rate - RATE_CHANGE * (j + 1);
				//�m����0��������ĂȂ���΁B+�ϓ��͂�قǂ̂��Ƃ��Ȃ�����1�����Ȃ����Ȃ�����
				if (job[i].rate > 0.0f)
				{
					//���s��`�q�ɋL�^����B
					m_currentGenetics.push_back(tables);
				}
			}

			//�ϓ������ɖ߂��Ă����B
			job[i].rate = rate;
		}
	}
}


