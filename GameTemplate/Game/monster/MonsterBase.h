#pragma once
#include "Skill/SkillBase.h"
#include "parameter/StatusManager.h"
#include "parameter/StatusUI.h"

//const int AI_SIZE = 6;							//AI���Ƃ肤��s���̐��B
//const int AI_SIZE = 6;							//AI���Ƃ肤��s���̐��B

struct Status;

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

/************************/
/*		���N���X		*/
/************************/
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
	StatusManager& GetStatusManager()
	{
		return m_status;
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
		m_status.SetStatus(status);
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

	void Draw();			//�`�揈���Ƃ����܂Ƃ߂����́B

	//�N�[���^�C����ݒ肷��B
	void SetCoolTime(float time)
	{
		m_status.SetCoolTime(time);
	}
	//HP��0�ɂȂ��Ă��邩�ǂ����B
	bool IsDeath() {
		return m_status.IsDeath();
	}

	//�s���̕]�����s���B
	virtual bool ACTScoring();

	//�s���̃��U���g�̐ݒ�B
	//!<No			�X�L���ԍ��B
	//!<damage		�_���[�W�l�B
	void SetActResult(int No ,int damage) {
		m_actRes.skillNo = No;
		m_actRes.damage = damage;
	}

	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	/// <returns>�������_���[�W�ʁB</returns>
	int Damage(int damage)
	{
		if (m_status.IsDeath()) return 0;
		//�A�j���[�V�����B
		m_animation.Play(en_anim_Damage, 0.3f);

		return m_status.Damage(damage);
	}

	/// <summary>
	/// HP���񕜂�����B
	/// </summary>
	/// <param name="healing">�񕜗ʁB</param>
	/// <returns>�񕜂ł����ʁB</returns>
	int Healing(int healing) {
		return m_status.Healing(healing);
	};

	/// <summary>
	/// �o�t��������B
	/// </summary>
	/// <param name="status">�o�t��������X�e�[�^�X�B</param>
	/// <param name="pow">�o�t�̈З́B</param>
	/// <param name="time">�o�t�̌��ʎ��ԁB</param>
	/// <returns>���ʒl�B</returns>
	int Monster_Buff(StatusBuff status,float pow,float time);

	//�o�t�����Z�b�g����B
	void ResetBuff(int i) 
	{
		m_status.ResetBuff(i);
	};

	/// <summary>
	/// �X�L���̃^�[�Q�b�g���߂�B
	/// </summary>
	/// <param name="e_team">�G�̃`�[���B</param>
	/// <param name="m_team">�����̃`�[���B</param>
	virtual void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team);

	//�s����������B
	virtual bool BattleAction() = 0;

	/// <summary>
	/// bin�t�@�C������f�[�^��ǂݍ��ށB
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	virtual void Init(const char* filePath);
	/// <summary>
	/// bin�t�@�C���Ƀf�[�^���������ށB
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	virtual void Save(const char* filePath);

protected:
	/// <summary>
	/// �f�t�H���g�̍s�������o���B
	/// </summary>
	virtual void MakeData() {};
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

	StatusManager m_status;								//�X�e�[�^�X�B

	//	AI�f�[�^�B
	std::vector<AIData> m_AI;							//AI�f�[�^�B
	char m_AIPath[64];									//AI�f�[�^�̃t�@�C���p�X�B
	ACTResullt m_actRes;								//�s���̃��U���g�B
	std::vector<ACTResullt> m_actResList;				//�s���̃��U���g�̉ϒ��z��B
	int m_scoringFlag = 0;								//�]���̃t���O�B

	//	�|�C���^�Ƃ��B
	std::vector<MonsterBase*> m_teamMenber;				//�����̃`�[���B
	SkillBase* m_useSkill = nullptr;					//�g�p���Ă���X�L���̃|�C���^�B
	MonsterBase* m_target = nullptr;					//�X�L���̑ΏہB

	//UI��\��������B
	StatusUI* m_UI;
};

