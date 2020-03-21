#pragma once
#include "Skill/SkillList.h"
#include "level/Level.h"

class MonsterBase;
class MonsterTeam1;
//class SkillList;
class Fade;
class GameCamera;

class BattleScenes : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	BattleScenes();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~BattleScenes();

	bool Start();
	void Update();
	//�����X�^�[�̏������B
	void InitMonster();

private:
	//�A�N�e�B�u�^�C���o�[�̍X�V�B
	void ActiveTimeUpdate();
	//�����X�^�[�ɍs��������B
	void MonsterAction();
	//�s���̕]�����s���B
	void MonsterScoring();
	//�t�F�[�h�؂�ւ�
	enum SceneState {
		enState_FadeIn,
		enState_Battle,
		enState_FadeOut
	};
	//�o�g���̏����؂�ւ�
	enum BattleState {
		enState_ATB,
		enState_ACT,
		enState_Scoring
	};

	Fade* m_fade = nullptr;
	SceneState m_state = enState_FadeIn;
	BattleState m_battleState = enState_ATB;
	Level m_level;
	//�����X�^�[�̃|�C���^�B
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;

	SkinModel m_model;						//!<�X�e�[�W�̃��f���B
	MonsterBase* m_monsterACT = nullptr;	//!<���ݍs�����̃����X�^�[�B
	std::vector<MonsterBase*>m_monsterACTList;	//!<�s�����̃��X�g�B
	float battleCoolTime = 0.0f;
	SkillList skillList;					//!<�X�L�����X�g�B
	GameCamera* m_camera = nullptr;			//!<�Q�[���J�����B
};

