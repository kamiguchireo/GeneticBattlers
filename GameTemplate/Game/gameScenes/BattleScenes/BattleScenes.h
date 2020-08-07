#pragma once
#include "Skill/SkillList.h"
#include "level/Level.h"
#include "BattleManager.h"

class MonsterBase;
class MonsterTeam1;
class Fade;
class GameCamera;
class NetScenes;

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
	void Draw();

	/// <summary>
	/// �����������ǂ����B
	/// ���łɃX�e�[�g�̐؂�ւ��B
	/// </summary>
	/// <param name="res">true ���� : false �s�k</param>
	void SetBattleResult(bool res)
	{
		m_isWin = res;
		battleCoolTime = 2.0f;
		m_state = enState_Result;
	}
private:
	/// <summary>
	/// UI�̍��W�����B
	/// </summary>
	static const CVector3 ATTAKER;			//UI���W(Attaker)
	static const CVector3 HEALER;			//UI���W(Healer)
	static const CVector3 SUPPORTER;		//UI���W(Supporter)
	static const CVector3 ENEMY_ATTACKER;	//UI���W(EnemyAttaker)
	static const CVector3 ENEMY_HEALER;		//UI���W(EnemyHealer)
	static const CVector3 ENEMY_SUPPORTER;	//UI���W(EnemySupporter)

private:
	//�t�F�[�h�؂�ւ�
	enum SceneState {
		enState_FadeIn,
		enState_Battle,
		enState_Result,
		enState_FadeOut
	};
	Fade* m_fade = nullptr;
	NetScenes* m_netScenes = nullptr;
	SceneState m_state = enState_FadeIn;
	Level m_level;
	SkinModel m_model;						//!<�X�e�[�W�̃��f���B

	BattleManager* m_battleManager = nullptr;	//�퓬�Ǘ��p�N���X�B
	GameCamera* m_camera = nullptr;			//!<�Q�[���J�����B
	prefab::SpriteRender* m_resultSprite = nullptr;	//!<���U���g�p�̃X�v���C�g�����_�[�B
	prefab::CSoundSource* m_bgm = nullptr;	//!<�T�E���h�\�[�X�B
	float m_bgmVol = 0.0f;
	float battleCoolTime = 0.0f;			//!<�N�[���^�C���B
	bool m_isWin = false;					//!<�����t���O�B
	bool m_isSprite = false;				//!<�X�v���C�g���\�����ꂽ���B
};

