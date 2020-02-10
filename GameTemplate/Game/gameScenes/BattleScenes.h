#pragma once
#include "Skill/SkillList.h"
#include "level/Level.h"

class MonsterBase;
class MonsterTeam1;
//class SkillList;
class Fade;

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
	//�����X�^�[�ɍs��������B
	void MonsterAction();

private:
	//�A�N�e�B�u�^�C���o�[�̍X�V�B
	void ActiveTimeUpdate();
	//�t�F�[�h�؂�ւ�
	enum SceneState {
		enState_FadeIn,
		enState_Battle,
		enState_FadeOut
	};
	Fade* m_fade = nullptr;
	SceneState m_state = enState_FadeIn;

	Level m_level;
	//�����X�^�[�̃|�C���^�B
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;

	SkinModel m_model;						//!<�X�e�[�W�̃��f���B
	MonsterBase* m_monsterACT = nullptr;	//!<���ݍs�����̃����X�^�[�B
	SkillList skillList;					//!<�X�L�����X�g�B
};

