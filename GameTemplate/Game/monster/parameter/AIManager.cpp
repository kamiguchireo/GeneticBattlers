#include "stdafx.h"
#include "AIManager.h"
#include "Skill/SkillDataLoad.h"

const float AIManager::SKILL_NEW_RATE = 0.3f;		//�ǉ��X�L���̏����g�p�䗦�B
const float AIManager::FIRST_RATE = 0.15f;			//�V�K�s���̏����䗦�B
const int AIManager::MAX_TARGET_COUNT = 3;			//�^�[�Q�b�g�̍ő吔�B


AIManager::AIManager()
{
}

AIManager::~AIManager()
{
}

bool AIManager::Load(const char * filePath)
{
	//�t�@�C���p�X���R�s�[���Ă����B
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//�ǂݍ��ݎ��s�B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "bin�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B%s\n", filePath);
		OutputDebugStringA(message);
#endif
		return false;
	}

	//�ǂݍ���ł����B
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);

	//�ǂݍ��ݐ����B
	return true;
}

void AIManager::LoadDefault(const char * filePath)
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
		m_AI.push_back(hoge);
	}

	fclose(fp);
}

void AIManager::Save()
{
	AIUpdate();
	AddNewSkill();

	FILE* fp = fopen(m_AIPath, "wb");

	if (fp == nullptr) {
		return;
	}

	//�f�[�^����������ł����B
	while (m_AI.size() != 0) {
		AIData hoge = m_AI.front();
		m_AI.erase(m_AI.begin());
		fwrite(&hoge, sizeof(AIData), 1, fp);
	}

	fclose(fp);
}

void AIManager::AIUpdate()
{
	//�s���]���ɂ��s��AI�̊m���̍X�V�B
	const int listSize = static_cast<const int>(m_actResList.size());
	int AISize = static_cast<int>(m_AI.size());
	std::vector<float> AIscoreList(AISize, 0.0f);		//�s�����Ƃ̃X�R�A�B
	float sum = 0.0f;
	//�X�R�A�����v����B
	for (auto& res : m_actResList) {
		////�]������Ă��Ȃ��B
		//if (!res.score)	continue;
		//�X�R�A�����v����B
		int i = 0;
		for (i = 0; i < AISize; i++) {
			//�����̍s���e�[�u���ɑ��݂���B
			if (res.skillNo == m_AI[i].skillNo
				&&res.target == m_AI[i].target) {
				AIscoreList[i] += res.damage;
				sum += res.damage;
				break;
			}
		}
		//���݂��Ȃ��B
		if (i == AISize) {
			//�s���ɒǉ��B
			AIData hoge;
			hoge.skillNo = res.skillNo;
			hoge.target = res.target;
			hoge.rate = FIRST_RATE;		//�ŏ����炠����x�̊m�����������Ă����B
			//�z��ɐςށB
			m_AI.push_back(hoge);
			AIscoreList.push_back(static_cast<float>(res.damage));
			AISize++;		//�T�C�Y���������B
		}
	}
	//0�������B
	sum = max(sum, 1.0f);
	//�䗦�v�Z�B
	for (int i = 0; i < AISize; i++) {
		AIscoreList[i] /= sum;
	}

	//�s���̕]���𔽉f����B
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate = m_AI[i].rate * 10.0f + AIscoreList[i];
	}
	//�g�p�����m���ɒ����B
	RateCalc();
}

void AIManager::AddNewSkill()
{
	//�X�L�����Ƃ̎g�p�����v�Z�B
	SkillRateCalc();

	//�X�L�����Ƃ̎g�p�������𒴂��Ă��邩�H
	std::vector<int> skillList;

	for (auto& sr : m_skillRateList)
	{
		if (sr.rate > SKILL_NEW_RATE)
		{
			skillList.push_back(sr.skillNo);
		}
	}
	//�����Ă�����̂��Ȃ��B���f�B
	if (skillList.size() == 0) return;

	//�X�L���̃f�[�^���擾�B
	auto skillData = SkillDataLoad::GetInstance();
	if (skillData == nullptr) return;

	//�ǉ�����X�L�������߂�B
	for (auto& No : skillList)
	{
		//�X�L���f�[�^�擾�B
		SkillData data = skillData->GetSkillData(No);

		int NextSkillSize = static_cast<int>(data.NextSkillNo.size());

		//���̃X�L���͂Ȃ��B
		if (NextSkillSize == 0) continue;

		AIData newData;

		//���̃X�L���T���B
		//�����B
		int r = g_random.GetRandomInt() % NextSkillSize;
		newData.skillNo = data.NextSkillNo[r];

		int i = 0;
		for (i = 0; i < m_skillRateList.size(); i++)
		{
			//�����X�L�������łɂ���B
			if (newData.skillNo == m_skillRateList[i].skillNo)	 break;
		}
		//���f�B
		if (i != m_skillRateList.size()) continue;

		for (int j = 0; j < MAX_TARGET_COUNT; j++)
		{
			//�^�[�Q�b�g���߂�B
			newData.target = j;
			//�g�p����K���Ɏ������Ă����B
			newData.rate = FIRST_RATE / MAX_TARGET_COUNT;		//�������炢�����傤�ǂ������Ȃ��H
			//�s�����X�g�ɐςށB
			m_AI.push_back(newData);
		}
	}

	//�m���ɖ߂��B
	RateCalc();
}

void AIManager::SkillRateCalc()
{
	//���X�g����ɂ��Ă����B
	m_skillRateList.clear();

	//�X�L�����Ƃ̎g�p�����v�Z�B
	for (auto& ai : m_AI)
	{
		int i = 0;
		for (i = 0; i < m_skillRateList.size(); i++) {
			//���X�g�ɑ��݂���B
			if (ai.skillNo == m_skillRateList[i].skillNo) {
				m_skillRateList[i].rate += ai.rate;
				break;
			}
		}
		//���݂��Ȃ��B
		if (i == m_skillRateList.size()) {
			//���X�g�ɒǉ��B
			SkillRate hoge;
			hoge.skillNo = ai.skillNo;
			hoge.rate = ai.rate;
			//�z��ɐςށB
			m_skillRateList.push_back(hoge);
		}
	}
}