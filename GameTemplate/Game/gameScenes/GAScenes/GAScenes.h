#pragma once
#include "monster/MonsterData.h"

namespace GA {
	enum Job
	{
		en_Attacker,
		en_Healer,
		en_Supporter,
		en_JobNum
	};

	typedef std::vector<AIData> AITable;		//AI���B
	typedef std::vector<AITable> AITableList;	//AI���e�[�u���B
	struct Genetic
	{
		AITableList genetic;		//��`�q�ƂȂ�AI���e�[�u���B
		int winRate = 0;			//�]���l�ƂȂ鏟��(%)�B
	};
	typedef std::vector<Genetic> GeneticsList;//AI���e�[�u���ō\��������`�q���B�������ɂ���͐[�����邩�Ȃ��H
}

class EvaluationCalculator;
class Fade;

class GAScenes:public IGameObject
{
public:
	GAScenes();
	~GAScenes();
	bool Start()override;
	void Update()override;
private:
	//�f�[�^��ǂݍ��ށB
	void LoadAIData(const char* filePath, GA::AITable& ai);
	//������`�q���쐬����B
	void FirstGenesCreate();
	//�����𑪒�B
	void CalcWinRate();
	//�]���l�Ń\�[�g���s���B
	void SortGenes();
	//�����̏����B
	void GeneSelection(); 
	//�����̏����B
	void GenesCrossover();
	//�m��������������B�B
	void GeneSwap(GA::AITable& _t1, GA::AITable& _t2);
	//�ˑR�ψق̏����B
	void Mutation();
	//AI�̊m����ϓ�������
	void GeneMutation(GA::AITable & _table);

	/// <summary>
	/// �P�D�����̑��菈���B�܂�͐퓬�������s���N���X���K�v�Ȃ̂ł�...
	///		�����ň�`�q���m���ɒ����Ă����Ȃ��Ƃł��˂�
	///		��Ōv�����ʂ��L�^����֐��ƕ]���l�Ń\�[�g����֐����K�v�ł��˂� �I��肩�Ȃ�
	/// �Q�D�����̏����B
	/// �R�D�ˑR�ψق̏����B
	/// </summary>


private:		//�萔�B
	static const float RATE_CHANGE;		//������`�q�������̊m���ϓ���
	static const int CHANGE_NUM;		//�m���ϓ��ō�鐔�B
	const int SELECT_ELETE = 20;		//�I������G���[�g�̐��B
	const int MAX_GENERATION = 50;		//�J��Ԃ����㐔�B
	const float MUTATION_RATE = 0.05;	//�ˑR�ψق̊m���B

	enum Scene {
		en_FadeIn,
		en_FirstGeneric,
		en_GA,
		en_End,
		en_FadeOut
	};

private:		//�����o�ϐ��B
	prefab::SpriteRender* m_sprite = nullptr;			//�w�i�摜�B
	prefab::FontRender* m_fontGeneration = nullptr;		//�t�H���g
	prefab::FontRender* m_fontWinRate = nullptr;		//�t�H���g
	Fade* m_fade = nullptr;		//�t�F�[�h�N���X�B
	Scene m_sceneState = en_FadeIn;

	EvaluationCalculator* m_evaluationCalc = nullptr;
	GA::AITable m_myAI[GA::en_JobNum];		//���ƂȂ�AI�̃f�[�^�B
	GA::AITable m_enemyAI[GA::en_JobNum];	//�G��AI�f�[�^�B
	GA::GeneticsList m_currentGenetics;	//���s����̈�`�q�B
	GA::GeneticsList m_eliteGenetics;		//�G���[�g��`�q�̃��X�g�B
	int m_geneSize = 0;		//��`�q�̃T�C�Y�B
	int m_currentGenerationNum = 0;		//���㐔�B
	int m_maxWinRate = 0;		//�ō���`�q�̏����B
};

