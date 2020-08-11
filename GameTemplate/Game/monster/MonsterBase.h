#pragma once
//#include "Skill/SkillBase.h"
#include "parameter/StatusManager.h"
#include "parameter/StatusUI.h"
#include "parameter/GAManager.h"

struct Status;

//�s���̃��U���g�B
//!<damage		�_���[�W�l�B
//!<skillNo		�X�L���ԍ��B
//!<target		�^�[�Q�b�g�l�B
//!<score		�]���B
struct ACTResullt {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
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
	virtual ~MonsterBase();

	void PreRender()override;
	void Update()override;
	void Draw()override;

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
	const StatusManager& GetStatusManager() const
	{
		return m_status;
	}
	//�`�[�������o�[���X�g���擾�B
	const std::vector<MonsterBase*>& GetTeamMenber()const
	{
		return m_teamMenber;
	}
	GAManager& GetGAManager()
	{
		return m_GAData;
	}
	//�X�e�[�^�X�̐ݒ�B
	//�����t�@�C�����烍�[�h�������B
	void SetStatus(int hp, int atk, int def, int mat, int mdf, int dex);
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
	//�g�嗦�̐ݒ�B
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//�G���������̐ݒ�B�f�t�H���gfalse(����),true(�G)
	void SetIsEnemy(bool flag = false)
	{
		m_isEnemy = flag;
	}
	//UI�̈ʒu��ݒ肷��B
	void SetUIPos(const CVector3& pos)
	{
		m_UIpos = pos;
	}
	//�����`�[���̃��X�g��ݒ�B
	void SetTeamMenber(const std::vector<MonsterBase*>& list)
	{
		m_teamMenber = list;
	}

	/// <summary>
	/// ���f���֌W�̏������N���X���������ق��������񂩂Ȃ��H
	/// </summary>

	//���@�̃A�j���[�V�������Đ��B
	void AnimationMagic()
	{
		m_animation.Play(en_anim_Magic, 0.3f);
	}
	//�U���̃A�j���[�V����
	void AnimationAttack()
	{
		m_animation.Play(en_anim_Attack, 0.3f);
	}
	//�ҋ@��Ԃ̃A�j���[�V�����B
	void AnimationIdle()
	{
		m_animation.Play(en_anim_Idle, 0.3f);
	}

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
	//�_���[�W�̃��U���g���擾�B
	void SetDamageResult(int res)
	{
		m_actRes.damage = res;
	}

	//�A�N�e�B�u�^�C�����Z�B
	bool AddATB()
	{
		return m_status.AddATB();
	}
	//�X�e�[�g�̃A�b�v�f�[�g�B
	void StateUpdate()
	{
		m_status.StateUpdate();
	}

	/// <summary>
	/// ���̕ӂ̏����X�e�[�^�X�̂ق��ł܂Ƃ߂��ق��������̂ł́H
	/// </summary>

	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	/// <returns>�������_���[�W�ʁB</returns>
	int Damage(int damage);

	/// <summary>
	/// HP���񕜂�����B
	/// </summary>
	/// <param name="healing">�񕜗ʁB</param>
	/// <returns>�񕜂ł����ʁB</returns>
	int Healing(int healing) {
		if (IsDeath()) return 0;		//���S���͉񕜂��Ȃ��B
		return m_status.Healing(healing);
	};

	/// <summary>
	/// �o�t��������B
	/// </summary>
	/// <param name="status">�o�t��������X�e�[�^�X�B</param>
	/// <param name="pow">�o�t�̈З́B</param>
	/// <param name="time">�o�t�̌��ʎ��ԁB</param>
	/// <returns>���ʒl�B</returns>
	int MonsterBuffAndDebuff(StatusBuff status,float pow,float time);

	/// <summary>
	/// �X�L���̃^�[�Q�b�g���߂�B
	/// </summary>
	/// <param name="e_team">�G�̃`�[���B</param>
	/// <param name="m_team">�����̃`�[���B</param>
	/// <param name="skill">�X�L���ԍ��̃o�b�t�@�B</param>
	/// <param name="target">�^�[�Q�b�g�ԍ��̃o�b�t�@�B</param>
	virtual void SelectUseSkill(
		const std::vector<MonsterBase*>& e_team, 
		const std::vector<MonsterBase*>& m_team,
		int& skill, int& target);

	/// <summary>
	/// bin�t�@�C������f�[�^��ǂݍ��ށB
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	void Init(const char* filePath);
private:
	static const float SOUND_VOL;

protected:
	/// <summary>
	/// �f�t�H���g�̍s���̃f�[�^��ǂݍ��ނ��߂̃t�@�C���p�X�B
	/// </summary>
	virtual const char* GetDefaultDataPath() = 0;

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
	CVector3 m_scale = CVector3::One();					//�g�嗦�B

	StatusManager m_status;								//�X�e�[�^�X�B

	//	AI�f�[�^�B
	GAManager m_GAData;									//�s���e�[�u���̃f�[�^�B
	ACTResullt m_actRes = { 0,0,0 };					//�s���̃��U���g�B
	int m_scoringFlag = 0;								//�]���̃t���O�B

	//	�|�C���^�Ƃ��B
	std::vector<MonsterBase*> m_teamMenber;				//�����̃`�[���B
	MonsterBase* m_target = nullptr;					//�X�L���̑ΏہB

	//UI��\��������B
	StatusUI* m_UI;
	CVector3 m_UIpos = CVector3::Zero();
	bool m_isEnemy = false;
};

