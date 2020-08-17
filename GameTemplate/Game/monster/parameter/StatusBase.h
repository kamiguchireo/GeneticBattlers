#pragma once

/// <summary>
/// �X�e�[�^�X�̍\���́B
/// </summary>
/// <remarks>
/// ���@�U���͂�INT����int�^�ƊԈႦ����������MAT�Ƃ����B
/// </remarks>
struct Status {
	int HP = 0,
		//MP		= 0,
		ATK = 0,
		DEF = 0,
		MAT = 0,
		MDF = 0,
		DEX = 0;
};

//�o�t�̗񋓁B
enum StatusBuff {
	en_buff_ATK,
	en_buff_DEF,
	en_buff_MAT,
	en_buff_MDF,
	en_buff_DEX,
	en_buff_NONE,
	en_buff_num
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

class CStatusBase
{
public:
	CStatusBase() {};
	virtual ~CStatusBase() {};

	//�X�e�[�^�X�̐ݒ�B
	//�����t�@�C�����烍�[�h�������B
	void SetStatus(const Status& status)
	{
		m_statusBase = status;
		m_status = m_statusBase;
	}
	//�X�e�[�^�X(�A�^�b�J�[�p)
	void StatusAttaker();
	//�X�e�[�^�X(�q�[���[�p)
	void StatusHealer();
	//�X�e�[�^�X(�q�[���[�p)
	void StatusSupporter();

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
	//���݂̃X�e�[�g�̎擾�B
	const MonsterState& GetState()const
	{
		return m_stateAI;
	}
	//�N�[���^�C����ݒ肷��B
	void SetCoolTime(float time)
	{
		m_coolTime = time;
	}
	//HP��0�ɂȂ��Ă��邩�ǂ����B
	bool IsDeath() {
		//return m_stateAI == en_state_Death;
		return m_IsDeath;
	}
	//���S�t���O��ݒ肷��B
	void SetDeath(bool flag) {
		m_IsDeath = flag;
	}
	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	/// <returns>�������_���[�W�ʁB</returns>
	int Damage(int damage)
	{
		//����HP�ƃ_���[�W�ʂ̔�r�B
		int res = min(m_status.HP, damage);
		m_status.HP -= res;
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
	int Monster_Buff(StatusBuff status, float pow, float time);
	/// <summary>
	/// �f�o�t���|����B
	/// </summary>
	/// <param name="status">�f�o�t��������X�e�[�^�X</param>
	/// <param name="pow"></param>
	/// <param name="time"></param>
	/// <returns></returns>
	int Monster_Debuff(StatusBuff status, float pow, float time);
	//�o�t�ƃf�o�t�̒l���X�e�[�^�X�ɍ��v����B
	void SumBufAndDebuff(int status);
	//�o�t�����Z�b�g����B
	void ResetBuff(int i);
	//�f�o�t�����Z�b�g����B
	void ResetDebuff(int i);

	/// <summary>
	/// �A�N�e�B�u�^�C���̉��Z�B
	/// </summary>
	/// <returns>���܂�؂������̔���B</returns>
	virtual bool AddATB() = 0;

	void ClearATB()
	{
		m_activeTime = 0.0f;
	}
	/// <summary>
	/// �X�e�[�g�̍X�V�����B
	/// </summary>
	/// <param name="ui"></param>
	virtual void StateUpdate() = 0;

protected:
	//	�X�e�[�^�X
	Status m_statusBase;								//��b�X�e�[�^�X�B
	Status m_status;									//�X�e�[�^�X�B
	MonsterState m_stateAI = en_state_Good;				//�X�e�[�g�B
	bool m_IsDeath = false;								//�L�����N�^�[���S�t���O�B
	float m_activeTime = 0.0f;							//�A�N�e�B�u�^�C���B
	float m_coolTime = 30.0f;							//�N�[���^�C���B
	float m_buffTimeList[en_buff_num] = { 0.0f };			//�o�t�^�C���B
	int m_buffValues[en_buff_num] = { 0 };					//�o�t�ɂ��㏸�l
	float m_debuffTimeList[en_buff_num] = { 0.0f };			//�f�o�t�^�C���B��邩�Ȃ��H
	int m_debuffValues[en_buff_num] = { 0 };				//�f�o�t�ɂ��ቺ�l
};

