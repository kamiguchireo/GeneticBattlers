#pragma once
#include "Skill/SkillBase.h"
#include "../StatusUI.h"

//const int AI_SIZE = 6;							//AI���Ƃ肤��s���̐��B

/// <summary>
/// �X�e�[�^�X�̍\���́B
/// </summary>
/// <remarks>
/// ���@�U���͂�INT����int�^�ƊԈႦ����������MAT�Ƃ����B
/// </remarks>
struct Status {
	int HP		= 0,
		//MP		= 0,
		ATK		= 0,
		DEF		= 0,
		MAT		= 0,
		MDF		= 0,
		DEX		= 0;
};

//�o�t�̗񋓁B
enum StatusBuff {
	en_buff_ATK,
	en_buff_DEF,
	en_buff_MAT,
	en_buff_MDF,
	en_buff_DEX,
	en_buff_num
};

//�s���e�[�u���̃f�[�^�B
//!<skillNo		�X�L���ԍ��B
//!<target		�^�[�Q�b�g�ԍ��B
//!<rate		�g�p�p�x�B
struct AIData {
	int skillNo = 0;
	int target = 0;
	float rate = 0.0f;
};

//�s���̃��U���g�B
//!<damage		�_���[�W�l�B
//!<skillNo		�X�L���ԍ��B
//!<target		�^�[�Q�b�g�l�B
//!<score		�]���B
struct ACTResullt {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
	bool score = false;
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
	virtual void Init(const char* filePath) {};
	/// <summary>
	/// bin�t�@�C���Ƀf�[�^���������ށB
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	virtual void Save(const char* filePath) {};

	//���W���擾�B
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
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
	//�`�[�������o�[���X�g���擾�B
	const std::vector<MonsterBase*> GetTeamMenber()const
	{
		return m_teamMenber;
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
	//��]�̐ݒ�B
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//UI�̈ʒu��ݒ肷��B
	virtual void SetUIPos(const CVector3& pos){}
	//�����`�[���̃��X�g��ݒ�B
	void SetTeamMenber(const std::vector<MonsterBase*>& list)
	{
		m_teamMenber = list;
	}
	//�`�揈���Ƃ����܂Ƃ߂����́B
	void Draw();
	//�A�N�e�B�u�^�C�������Z����B
	bool AddATB();
	//�s���̕]�����s���B
	virtual bool ACTScoring();
	//�s���̃��U���g�̐ݒ�B
	//!<No			�X�L���ԍ��B
	//!<damage		�_���[�W�l�B
	void SetActResult(int No ,int damage) {
		m_actRes.skillNo = No;
		m_actRes.damage = damage;
	}
	//�N�[���^�C����ݒ肷��B
	void SetCoolTime(float time)
	{
		m_coolTime = time;
	}
	//
	bool IsDeath() {
		return m_stateAI == en_state_Death;
	}
	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	/// <returns>�������_���[�W�ʁB</returns>
	int Damage(int damage)
	{
		//����HP�ƃ_���[�W�ʂ̔�r�B
		int res = min(m_status.HP,damage);
		m_status.HP -= res;
		//�A�j���[�V�����B
		m_animation.Play(en_anim_Damage, 0.3f);

		return res;
	}
	/// <summary>
	/// HP���񕜂�����B
	/// </summary>
	/// <param name="healing">�񕜗ʁB</param>
	/// <returns>�񕜂ł����ʁB</returns>
	int Healing(int healing);

	/// <summary>
	/// �o�t��������B
	/// </summary>
	/// <param name="status">�o�t��������X�e�[�^�X�B</param>
	/// <param name="pow">�o�t�̈З́B</param>
	/// <param name="time">�o�t�̌��ʎ��ԁB</param>
	/// <returns>���ʒl�B</returns>
	int Monster_Buff(StatusBuff status,float pow,float time);
	//�o�t�����Z�b�g����B
	void ResetBuff(int i);

	/// <summary>
	/// �X�L���̃^�[�Q�b�g���߂�B
	/// </summary>
	/// <param name="e_team">�G�̃`�[���B</param>
	/// <param name="m_team">�����̃`�[���B</param>
	virtual void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team);
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
	//��`�I�A���S���Y����p���čs���e�[�u�����X�V�B
	void GIUpdate();
	//	���f���֌W
	SkinModel m_model;									//���f���f�[�^�B
	//�A�j���[�V�����̗񋓁B
	enum enAnimation {
		en_anim_Idle,
		en_anim_Attack,
		en_anim_Magic,
		en_anim_Damage,
		en_anim_Death,
		en_anim_num
	};
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animClip[en_anim_num];				//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B

	//	�X�e�[�^�X
	Status m_statusBase;								//��b�X�e�[�^�X�B
	Status m_status;									//�X�e�[�^�X�B
	AIData m_AI[6];										//AI�f�[�^�B
	char m_AIPath[64];									//AI�f�[�^�̃t�@�C���p�X�B
	ACTResullt m_actRes;								//�s���̃��U���g�B
	std::vector<ACTResullt> m_actResList;				//�s���̃��U���g�̉ϒ��z��B
	int m_scoringFlag = 0;								//�]���̃t���O�B
	int m_stateAI = en_state_Good;						//�X�e�[�g�B
	bool m_IsDeath = false;								//���S�t���O�B
	const float addTime = 1.0f / 144.0f * 4.0f;			//���Z�^�C���B
	float m_activeTime = 0.0f;							//�A�N�e�B�u�^�C���B
	float m_coolTime = 30.0f;							//�N�[���^�C���B
	float buffTimeList[en_buff_num] = { 0.0f };			//�o�t�^�C���B
	Elements m_elemnts = en_elements_Empty;				//�����B

	//	�|�C���^�Ƃ��B
	std::vector<MonsterBase*> m_teamMenber;				//�����̃`�[���B
	SkillBase* m_useSkill = nullptr;					//�g�p���Ă���X�L���̃|�C���^�B
	MonsterBase* m_target = nullptr;					//�X�L���̑ΏہB

	//UI��\��������B
	StatusUI* m_UI;
};

