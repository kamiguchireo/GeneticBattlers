#include "stdafx.h"
#include "GAScenes.h"
#include "../BattleScenes/AIResouce.h"
#include "EvaluationCalculator.h"
#include "Fade.h"
#include "../TitleScene.h"

using namespace GA;

const float GAScenes::RATE_CHANGE = 0.03f;	//������`�q�����̂��߂̊m���ϓ����B
const int GAScenes::CHANGE_NUM = 2;	//�m���ϓ��ō�鐔�B

GAScenes::GAScenes()
{
	//�f�[�^�ǂݍ��݁B
	LoadAIData("Assets/AIData/Attacker.bin", m_myAI[en_Attacker]);
	LoadAIData("Assets/AIData/Healer.bin", m_myAI[en_Healer]);
	LoadAIData("Assets/AIData/Supporter.bin", m_myAI[en_Supporter]);
	//LoadAIData("Assets/AIData/DefaultData/AttackerDefault.bin", m_myAI[en_Attacker]);
	//LoadAIData("Assets/AIData/DefaultData/HealerDefault.bin", m_myAI[en_Healer]);
	//LoadAIData("Assets/AIData/DefaultData/SupporterDefault.bin", m_myAI[en_Supporter]);

	auto aiResouce = AIResouce::GetInstance();
	if (aiResouce != nullptr)
	{
		m_enemyAI[en_Attacker] = aiResouce->GetAttacker();
		m_enemyAI[en_Healer] = aiResouce->GetHealer();
		m_enemyAI[en_Supporter] = aiResouce->GetSupporter();
		DeleteGO(aiResouce);
	}
	m_evaluationCalc = NewGO<EvaluationCalculator>(0);
	//�G��AI��ݒ肵�Ă����B
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Attacker], en_Attacker);
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Healer], en_Healer);
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Supporter], en_Supporter);
}

GAScenes::~GAScenes()
{
	if (m_evaluationCalc != nullptr)
	{
		DeleteGO(m_evaluationCalc);
	}
	DeleteGO(m_sprite);
	DeleteGO(m_fontGeneration);
	DeleteGO(m_fontWinRate);
}

bool GAScenes::Start()
{
	//�s���̐����L�^�B
	m_geneSize = 0;
	for (auto& ai : m_myAI)
	{
		m_geneSize += static_cast<int>(ai.size());
	}
	//�w�i�摜�B
	m_sprite = NewGO<prefab::SpriteRender>(0);
	m_sprite->Init(
		L"Assets/sprite/BackWindow.dds",
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//�t�H���g�B
	m_fontGeneration = NewGO<prefab::FontRender>(0);
	m_fontGeneration->SetPivot({ 0.5f,0.5f });
	m_fontGeneration->SetPosition({ 0.0f,200.0f });
	m_fontWinRate = NewGO<prefab::FontRender>(0);
	m_fontWinRate->SetPivot({ 0.5f,0.5f });
	m_fontWinRate->SetPosition({ 0.0f,-200.0f });
	wchar_t generationText[64];
	swprintf(generationText, L"�������B", m_currentGenerationNum);
	m_fontGeneration->SetText(generationText);

	wchar_t winRateText[64];
	swprintf(winRateText, L"�ō�����%3d�� : ���Ϗ���%3.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);

	m_fade = Fade::GetInstance();
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
			m_sceneState = en_FirstGeneric;
		}
		break;
	case GAScenes::en_FirstGeneric:
		//������`�q����������쐬�B
		FirstGenesCreate();
		//�]���l���v�Z����B
		CalcWinRate();
		//�]���l�Ń\�[�g�B
		SortGenes();
		wchar_t generationText[64];
		swprintf(generationText, L"��%3d����", m_currentGenerationNum);
		m_fontGeneration->SetText(generationText);

		wchar_t winRateText[64];
		swprintf(winRateText, L"�ō�����%3d�� : ���Ϗ���%3.2f��", m_maxWinRate, m_aveWinRate);
		m_fontWinRate->SetText(winRateText);

		m_sceneState = en_GA;
		break;
	case GAScenes::en_GA:
		if (m_currentGenerationNum < MAX_GENERATION)
		{
			GeneSelection();	//�����B
			GenesCrossover();	//�����B
			Mutation();			//�ˑR�ψفB
			CalcWinRate();		//�]���B�N�\�x���B
			SortGenes();		//�\�[�g�B
			wchar_t generationText[64];
			swprintf(generationText, L"��%3d����", m_currentGenerationNum);
			m_fontGeneration->SetText(generationText);

			wchar_t winRateText[64];
			swprintf(winRateText, L"�ō�����%3d�� : ���Ϗ���%3.2f��", m_maxWinRate,m_aveWinRate);
			m_fontWinRate->SetText(winRateText);
		}
		else
		{
			wchar_t generationText[64];
			swprintf(generationText, L"�I�����܂����B\nA�{�^���Ń^�C�g���ɖ߂�܂��B");
			m_fontGeneration->SetText(generationText);
			m_sceneState = en_End;
		}
		break;
	case GAScenes::en_End:
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_sceneState = en_FadeOut;
			m_fade->StartFadeOut();
		}
		break;
	case GAScenes::en_FadeOut:
		if (!m_fade->IsFade())	//�t�F�[�h�A�E�g���I������B
		{
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
	//��`�q�̐��B
	int genesSize = m_currentGenetics.size();

	//��`�q���̏����v�Z�B
	for (int i = 0; i < genesSize; i++)
	{
		m_currentGenetics[i].winRate  = m_evaluationCalc->Calculation(m_currentGenetics[i].genetic);
	}
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
		[](const Genetic& a, const Genetic& b) {return a.winRate > b.winRate; });

	//��ԗD�G�Ȉ�`�q�̏������L�^�B
	m_maxWinRate = (*m_currentGenetics.begin()).winRate;
	//���Ϗ����ł��B
	float sum = 0.0f;
	for (auto& gene : m_currentGenetics)
	{
		sum += gene.winRate;
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

	////�v�f���Ɣ��胁���h�C�B
	//float pRate = MUTATION_RATE * AISize;

	////1�𒴂��Ă���Ȃ�m��łǂ�����ϓ��B
	//while (pRate > 1.0f)
	//{
	//	int point = g_random.GetRandomInt() % AISize;
	//	float changeRange = 0.01f * (g_random.GetRandomInt() % 5 - 2);		//�ϓ�������l�����߂�B
	//	_table[point].rate += changeRange;

	//	pRate -= 1.0f;
	//}
	////�m���ł̕ϓ��B
	//if (pRate > (g_random.GetRandomInt() % 100) / 100)
	//{
	//	int point = g_random.GetRandomInt() % AISize;
	//	float changeRange = 0.01f * (g_random.GetRandomInt() % 5 - 2);		//�ϓ�������l�����߂�B
	//	_table[point].rate += changeRange;
	//}

}


