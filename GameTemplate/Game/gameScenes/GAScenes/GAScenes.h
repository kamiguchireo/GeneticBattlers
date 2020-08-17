#pragma once
#include "monster/MonsterData.h"

enum Job
{
	en_Attacker,
	en_Healer,
	en_Supporter,
	en_JobNum
};

class EvaluationCalculator;

typedef std::vector<AIData> AITable;		//AI���B
typedef std::vector<AITable> AITableList;	//AI���e�[�u���B
struct Genetic
{
	AITableList genetic;		//��`�q�ƂȂ�AI���e�[�u���B
	int winRate = 0;			//�]���l�ƂȂ鏟��(%)�B
};
typedef std::vector<Genetic> AIGenetics;//AI���e�[�u���ō\��������`�q���B�������ɂ���͐[�����邩�Ȃ��H

class GAScenes:public IGameObject
{
public:
	GAScenes();
	~GAScenes();
	bool Start()override;
	void Update()override;
private:
	//�f�[�^��ǂݍ��ށB
	void LoadAIData(const char* filePath, AITable& ai);
	//������`�q���쐬����B
	void FirstGenesCreate();
	//�����𑪒�B
	void CalcWinRate();
	//�]���l�Ń\�[�g���s���B
	void SortGenes();

	/// <summary>
	/// �P�D�����̑��菈���B�܂�͐퓬�������s���N���X���K�v�Ȃ̂ł�...
	///		�����ň�`�q���m���ɒ����Ă����Ȃ��Ƃł��˂�
	///		��Ōv�����ʂ��L�^����֐��ƕ]���l�Ń\�[�g����֐����K�v�ł��˂� �I��肩�Ȃ�
	/// �Q�D�����̏����B
	/// �R�D�ˑR�ψق̏����B
	/// </summary>


	static const int GENETICS_NUM = 100;
	static const float RATE_CHANGE;		//������`�q�������̊m���ϓ���
	static const int CHANGE_NUM;		//�m���ϓ��ō�鐔�B

	prefab::SpriteRender* m_sprite = nullptr;
	prefab::FontRender* m_font = nullptr;
	EvaluationCalculator* m_evaluationCalc = nullptr;
	AITable m_myAI[en_JobNum];		//���ƂȂ�AI�̃f�[�^�B
	AITable m_enemyAI[en_JobNum];	//�G��AI�f�[�^�B
	AIGenetics m_currentGenetics;	//���s����̈�`�q�B
	int m_actionNum = 0;		//��`�q�̍\���f�[�^���B
};
