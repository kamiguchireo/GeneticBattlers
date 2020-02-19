#pragma once
#include "Skill/SkillBase.h"
//�O���錾�B
struct SkillData;
//enum Elements;
//class SkillBase;

const int ActionNum = 10;							//AI���Ƃ肤��s���̐��B

/// <summary>
/// �X�e�[�^�X�̍\���́B
/// </summary>
/// <remarks>
/// ���@�U���͂�INT����int�^�ƊԈႦ����������MAT�Ƃ����B
/// </remarks>
struct Status {
	int HP		= 0,
		MP		= 0,
		ATK		= 0,
		DEF		= 0,
		MAT		= 0,
		MDF		= 0,
		DEX		= 0;
};

struct AIData {
	int skillNo = 0;
	float rate = 0.0f;
};

/// <summary>
/// �����X�^�[�X�e�[�g�B
/// </summary>
/// <remarks>
/// �ő�HP��3����1���݂ŃX�e�[�g�͕ς��\��B
/// </remarks>
enum MonsterState {
	en_state_Good,		//�c��HP�������B
	en_state_Usually,	//�c��HP�������O��B
	en_state_Bad,		//�c��HP���Ⴂ�B
	en_state_Death,		//�c��HP��0�B
	en_state_Num		//�X�e�[�g�̐��B
};

class MonsterBase:public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	MonsterBase();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~MonsterBase();

	/// <summary>
	/// bin�t�@�C������f�[�^��ǂݍ��ށB
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	void Init(const wchar_t* filePath);

	//���W���擾�B
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	//�X�e�[�^�X���擾�B
	const Status& GetStatus() const
	{
		return m_status;
	}
	//��b�X�e�[�^�X���擾�B
	const Status& GetStatusBase() const
	{
		return m_statusBase;
	}
	//�����X�^�[�̑������擾�B
	const Elements& GetElements() const
	{
		return m_elemnts;
	}
	//�X�e�[�^�X�̐ݒ�B
	//�����t�@�C�����烍�[�h�������B
	void SetStatus(int hp, int mp, int atk, int def, int mat, int mdf, int dex);
	//�X�e�[�^�X�̐ݒ�B(�X�e�[�^�X�\����ver)�B
	void SetStatus(const Status& status)
	{
		m_statusBase = status;
		m_status = m_statusBase;
	}
	//���W�̐ݒ�B
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�`�揈���B
	void Draw();
	//�A�N�e�B�u�^�C�������Z����B
	bool AddATB();
	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	void Damage(int damage)
	{
		m_status.HP -= damage;
		m_status.HP = max(0, m_status.HP);
	}
	/// <summary>
	/// HP���񕜂�����B
	/// </summary>
	/// <param name="healing">�񕜗ʁB</param>
	void Healing(int healing)
	{
		m_status.HP += healing;
		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}
	/// <summary>
	/// MP���񕜂�����B
	/// </summary>
	/// <param name="healing">�񕜗ʁB</param>
	void HealingMP(int healing)
	{
		m_status.MP += healing;
		m_status.MP = min(m_status.MP, m_statusBase.MP);
	}
	/// <summary>
	/// MP���g���B
	/// </summary>
	/// <param name="mp">����MP�ʁB</param>
	bool UseMP(int mp)
	{
		if (m_status.MP < mp) {
			return false;	//MP������Ȃ��Ƃ��̏����B
		}
		m_status.MP -= mp;
		return true;
	}
	/// <summary>
	/// �X�L���̃^�[�Q�b�g���߂�B
	/// </summary>
	/// <param name="list">�^�[�Q�b�g��I�Ԃ��߂̃��X�g</param>
	void SelectUseSkill(const std::vector<MonsterBase*>& list);
	/// <summary>
	///�X�e�[�g�̍X�V�����B 
	/// </summary>
	void StateUpdate();
	/// <summary>
	/// �X�e�[�g�ɉ����čs�������߂�B
	/// </summary>
	bool Action();

	virtual bool Action_good() { return false; }
	virtual bool Action_usually() { return false; }
	virtual bool Action_bad() { return false; }
	virtual bool BattleAction() = 0;
	

protected:
	SkinModel m_model;									//���f���f�[�^�B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	Status m_statusBase;								//��b�X�e�[�^�X�B
	Status m_status;									//�X�e�[�^�X�B
	AIData m_AI[3][ActionNum];							//AI�f�[�^�B
	bool m_isDeath = false;								//�퓬�s�\�t���O�B
	int m_stateAI = en_state_Good;						//�X�e�[�g�B
	float m_activeTime = 0.0f;							//�A�N�e�B�u�^�C���B
	Elements m_elemnts = en_elements_Empty;				//�����B
	SkillBase* m_useSkill = nullptr;					//�g�p���Ă���X�L���̃|�C���^�B
	MonsterBase* m_target = nullptr;					//�X�L���̑ΏہB
};

