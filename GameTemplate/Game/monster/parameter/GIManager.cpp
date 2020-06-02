#include "stdafx.h"
#include "GIManager.h"

GIManager::GIManager()
{
}

GIManager::~GIManager()
{
}

bool GIManager::Load(const char * filePath)
{
	//�t�@�C���p�X���R�s�[���Ă����B
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//�ǂݍ��ݎ��s�B
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

void GIManager::LoadDefault(const char * filePath)
{
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		return;
	}

	//�ǂݍ���ł����B
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);
}

void GIManager::Save()
{
	GIUpdate();

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

void GIManager::GIUpdate()
{
	//GI��p���čs��AI�̊m���̍X�V�B?
	const int listSize = m_actResList.size();
	int AISize = m_AI.size();
	std::vector<float> AIscoreList(AISize, 0.0f);		//�s�����Ƃ̃X�R�A�B
	float sum = 0.0f;
	//�X�R�A�����v����B
	for (auto res : m_actResList) {
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
			hoge.rate = 3.0f;		//�ŏ����炠����x�̊m�����������Ă����B
			//�z��ɐςށB
			m_AI.push_back(hoge);
			AIscoreList.push_back(res.damage);
			AISize++;		//�T�C�Y���������B
		}
	}
	//0�������B
	sum = max(sum, 1.0f);
	//�䗦�v�Z�B
	for (int i = 0; i < AISize; i++) {
		AIscoreList[i] /= sum;
	}

	sum = 0.0f;
	//�s���̕]���𔽉f����B
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate = m_AI[i].rate * 10.0f + AIscoreList[i];
		sum += m_AI[i].rate;
	}
	//�m���ɖ߂��B
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate /= sum;
	}
}

void GIManager::ActionDicide(int * skill, int * target)
{
	//�ˑR�ψٓI��
	int pMutation = rand() % 100;
	//100���̂P�̊m���B
	if (pMutation == 0) {
		//�����_���ɐ���������B
		int actNum = rand() % m_AI.size();
		*skill = m_AI[actNum].skillNo;
		*target = m_AI[actNum].target;//�ˑR�ψٓI��
		int pMutation = rand() % 100;

		//�֐��𔲂���B
		return;
	}
	int res = rand() % 100;	//�K���ȗ����B
	int sum = 0;

	//�s���e�[�u�������Ƃɍs��������B
	for (int i = 0; i < m_AI.size(); i++) {
		sum += (int)(m_AI[i].rate * 100);
		if (sum > res) {
			*skill = m_AI[i].skillNo;
			*target = m_AI[i].target;
			break;
		}
	}
}
