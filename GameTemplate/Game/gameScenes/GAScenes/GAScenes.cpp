#include "stdafx.h"
#include "GAScenes.h"
#include "../BattleScenes/AIResouce.h"
#include "EvaluationCalculator.h"
#include "Fade.h"
#include "../TitleScene.h"
#include "GASceneUI.h"

using namespace GA;

const float GAScenes::RATE_CHANGE = 0.03f;	//������`�q�����̂��߂̊m���ϓ����B
const int GAScenes::CHANGE_NUM = 2;	//�����m���ϓ��ō�鐔�B

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
	else
	{
		m_isError = true;
	}
	m_evaluationCalc = NewGO<EvaluationCalculator>(0);
	//�G��AI��ݒ肵�Ă����B
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Attacker], en_Attacker);
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Healer], en_Healer);
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Supporter], en_Supporter);
	//UI��\������N���X�쐬�B
	m_ui = NewGO<GASceneUI>(1);
	m_ui->SetEndGeneration(MAX_GENERATION);
}

GAScenes::~GAScenes()
{
	if (m_evaluationCalc != nullptr)
	{
		DeleteGO(m_evaluationCalc);
	}
	DeleteGO(m_ui);
}

bool GAScenes::Start()
{
	//�s���̐����L�^�B
	m_geneSize = 0;
	for (auto& ai : m_myAI)
	{
		m_geneSize += static_cast<int>(ai.size());
	}

	//������`�q����������쐬�B
	FirstGenesCreate();
	m_currentCalcSize = m_currentGenetics.size();		//���݂̈�`�q�����L�^�B

	m_fade = Fade::GetInstance();		//�t�F�[�h�N���X�擾�B
	m_fade->StartFadeIn();
	m_sceneState = en_FadeIn;

	return true;
}

void GAScenes::Update()
{
	switch (m_sceneState)
	{
	case GAScenes::en_FadeIn:
		if (!m_fade->IsFade())
		{
			//�ǂݍ��ݎ��s�B
			if (m_isError) {
				m_ui->SetErrorMasage();
				m_sceneState = en_End;		//�I���B
			}
			else {
				m_sceneState = en_Calc;		//�v�Z���n�߂�B
			}
		}
		break;
	case GAScenes::en_GA:		//�����i�߂�B
		if (m_currentGenerationNum < MAX_GENERATION)
		{
			GeneSelection();	//�����B
			GenesCrossover();	//�����B
			Mutation();			//�ˑR�ψفB
			m_currentCalcSize = m_currentGenetics.size();	//���݂̈�`�q�����L�^�B

			//CalcWinRate();		//�]���B�N�\�x���B
			//SortGenes();		//�\�[�g�B

			//�e�L�X�g�ύX�B
			m_ui->SetWinRate(m_currentGenerationNum, m_maxWinRate, m_aveWinRate);

			m_sceneState = en_Calc;		//�]���v�Z�Ɉڂ�B
		}
		else
		{
			//�e�L�X�g�ύX�B
			m_ui->EndWinRate(m_maxWinRate, m_aveWinRate);

			m_sceneState = en_End;		//GA���I������B
		}
		break;
	case GAScenes::en_Calc:		//�v�Z�𖈃t���[���s���B
		if (m_currentCalc < m_currentCalcSize)		//�v�Z�r�����H
		{
			CalcWinRate();	//�v�Z�𖈃t���[���s���Ă��炤�B
		}
		else
		{
			SortGenes();		//�]���l�Ń\�[�g�B

			m_currentCalc = 0;
			m_sceneState = en_GA;		//��`�q��ύX����B
		}
		break;
	case GAScenes::en_End:		//�I���BA�{�^���҂��B
		if (g_pad[0].IsTrigger(enButtonA))
		{
			//����ɏI���ł�����B
			if (!m_isError)
			{
				//�L�^�B
				SaveAIData("Assets/AIData/Attacker.bin", m_currentGenetics.front().genetic[en_Attacker]);
				SaveAIData("Assets/AIData/Healer.bin", m_currentGenetics.front().genetic[en_Healer]);
				SaveAIData("Assets/AIData/Supporter.bin", m_currentGenetics.front().genetic[en_Supporter]);
			}

			m_sceneState = en_FadeOut;
			m_fade->StartFadeOut();
		}
		break;
	case GAScenes::en_FadeOut:	
		if (!m_fade->IsFade())	//�t�F�[�h�A�E�g���I������B
		{
			//�t�F�[�h�A�E�g��^�C�g���ցB
			DeleteGO(this);
			NewGO<TitleScene>(0, nullptr);
		}
		break;
	default:
		break;
	}
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
		m_isError = true;
		return;
	}

	//�ǂݍ���ł����B
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		ai.push_back(hoge);
	}

	fclose(fp);
}

void GAScenes::SaveAIData(const char * filePath, GA::AITable & ai)
{
	FILE* fp = fopen(filePath, "wb");

	if (fp == nullptr) {
		return;
	}

	for (auto& data : ai)
	{
		AIData hoge = data;
		fwrite(&hoge, sizeof(AIData), 1, fp);
	}

	////�f�[�^����������ł����B
	//while (ai.size() != 0) {
	//	AIData hoge = ai.front();
	//	ai.erase(ai.begin());
	//	fwrite(&hoge, sizeof(AIData), 1, fp);
	//}

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
	m_currentGenetics.push_back({ tables,0 });
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
				m_currentGenetics.push_back({ tables,0 });

				//�m����-�ɕϓ�������B
				job[i].rate = rate - RATE_CHANGE * (j + 1);
				//�m����0��������ĂȂ���΁B+�ϓ��͂�قǂ̂��Ƃ��Ȃ�����1�����Ȃ����Ȃ�����
				if (job[i].rate > 0.0f)
				{
					//���s��`�q�ɋL�^����B
					m_currentGenetics.push_back({ tables,0 });
				}
			}

			//�ϓ������ɖ߂��Ă����B
			job[i].rate = rate;
		}
	}
}

void GAScenes::CalcWinRate()
{
	////��`�q�̐��B
	//int genesSize = m_currentGenetics.size();

	////��`�q���̏����v�Z�B
	//for (int i = 0; i < genesSize; i++)
	//{
	//	m_currentGenetics[i].winRate  = m_evaluationCalc->Calculation(m_currentGenetics[i].genetic);
	//}

	//��`�q���̏����v�Z�B�������50�~���b���炢�Œ�ł��������ĂȂ��H
	//1�t���[���P��ő����}�V�ɂȂ邩�Ȃ����炢�B
	m_currentGenetics[m_currentCalc].result  = m_evaluationCalc->Calculation(m_currentGenetics[m_currentCalc].genetic);
	
	m_currentCalc++;
}

void GAScenes::SortGenes()
{
	//�G���[�g�����s����Ɋ܂߂�B
	for (auto&elite : m_eliteGenetics)
	{
		m_currentGenetics.push_back(elite);
	}
	//�G���[�g���N���A
	m_eliteGenetics.clear();

	//���s��`�q�̃\�[�g���s���B
	std::sort(m_currentGenetics.begin(), m_currentGenetics.end(),
		[](const Genetic& a, const Genetic& b) {
			if (a.result.winRate > b.result.winRate)
			{
				return true;
			}
			else if (a.result.winRate == b.result.winRate)
			{
				return a.result.actionCount < b.result.actionCount;
			}
			return false;
		}
	);

	//��ԗD�G�Ȉ�`�q�̏������L�^�B
	m_maxWinRate = (*m_currentGenetics.begin()).result.winRate;
	//���Ϗ����ł��B
	float sum = 0.0f;
	for (auto& gene : m_currentGenetics)
	{
		sum += gene.result.winRate;
	}
	m_aveWinRate = sum / m_currentGenetics.size();

	//���㐔+1
	m_currentGenerationNum++;
}

void GAScenes::GeneSelection()
{
	//��`�q�̐����L�^
	int eliteSize = static_cast<int>(m_currentGenetics.size());
	//�c�����Ƃ̔�r�B
	eliteSize = min(eliteSize, SELECT_ELETE);

	//�G���[�g��`�q�̃��X�g������
	m_eliteGenetics.resize(eliteSize);
	//�G���[�g���R�s�[�B
	for (int i = 0; i < eliteSize; i++)
	{
		m_eliteGenetics[i] = m_currentGenetics[i];
	}
	//���s�������ɂ��Ă����B
	m_currentGenetics.clear();
}

void GAScenes::GenesCrossover()
{
	//�����̂��߂ɃG���[�g���R�s�[�B
	GeneticsList crossGenes1 = m_eliteGenetics;
	GeneticsList crossGenes2 = m_eliteGenetics;

	int crossSize = static_cast<int>(m_eliteGenetics.size());

	//�����B
	for (int i = 0; i < crossSize; i++)
	{
		//�E�Ƃ��Ƃɍs���B
		for (int j = 0; j < GA::en_JobNum; j++)
		{
			GeneSwap(
				crossGenes1[i].genetic[j],						//i�Ԗڂ̈�`�q
				crossGenes2[(i + 1) % crossSize].genetic[j]		//i+1�Ԗڂ̈�`�q
			);
		}
	}

	//���s����ɋL�^���Ă����B�]���l��0�ɖ߂��Ă����B
	for (auto&cross1 : crossGenes1)
	{
		m_currentGenetics.push_back({ cross1.genetic,0 });
	}
	for (auto&cross2 : crossGenes2)
	{
		m_currentGenetics.push_back({ cross2.genetic,0 });
	}
	//�f�[�^���N���A�B
	crossGenes1.clear();
	crossGenes2.clear();
}

void GAScenes::GeneSwap(AITable & _t1, AITable & _t2)
{
	//�T�C�Y���Ⴄ�B
	if (_t1.size() != _t2.size()) return;
	////�z��̃T�C�Y�B
	int maxSize = _t1.size();
	//��������ꏊ�����߂�B
	int pMax = g_random.GetRandomInt() % maxSize;
	pMax = min(pMax + 5, (maxSize-1));	//������x���l���������Ă����B0���������܂ށB
	int pMin = g_random.GetRandomInt() % pMax;
	//�����B
	for (int i = pMin; i <= pMax; i++)
	{
		//�m���������B
		std::swap(_t1[i].rate, _t2[i].rate);
	}

}

void GAScenes::Mutation()
{
	//�ˑR�ψق��s���Ă����B
	for (auto& gene : m_currentGenetics)
	{
		for (int i = 0; i < en_JobNum; i++)		//���[�����ɍs���B
		{
			GeneMutation(gene.genetic[i]);
		}
	}
}

void GAScenes::GeneMutation(AITable & _table)
{
	//�z��̑傫���B
	int AISize = _table.size();

	for (auto& ai : _table)
	{	
		//�m���ł̕ϓ��B
		if (MUTATION_RATE > (static_cast<float>((g_random.GetRandomInt() % 100)) / 100))
		{
			int changeRange = static_cast<int>(g_random.GetRandomInt()) % 5 - 2;
			float changeRate = 0.05f * static_cast<float>(changeRange);		//�ϓ�������l�����߂�B
			ai.rate += changeRate;

			ai.rate = max(0.0f, ai.rate);		//0���Ⴍ�͂Ȃ�Ȃ��B
		}

	}
}


