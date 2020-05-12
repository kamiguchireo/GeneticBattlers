#pragma once

class StatusUI;

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

//�X�e�[�^�X���Ǘ�����N���X�B
class StatusManager
{
public:
	StatusManager() {};
	~StatusManager() {};

	//�X�e�[�^�X�̐ݒ�B
	//�����t�@�C�����烍�[�h�������B
	void SetStatus(const Status& status)
	{
		m_statusBase = status;
		m_status = m_statusBase;
	}
	void SetUI(StatusUI* UI)
	{
		m_UI = UI;
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
	const MonsterState& GetState()const
	{
		return m_stateAI;
	}
	////�����X�^�[�̑������擾�B
	//const Elements& GetElements() const
	//{
	//	return m_elemnts;
	//}
	//�N�[���^�C����ݒ肷��B
	void SetCoolTime(float time)
	{
		m_coolTime = time;
	}
	//HP��0�ɂȂ��Ă��邩�ǂ����B
	bool IsDeath() {
		return m_stateAI == en_state_Death;
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

	//�o�t�����Z�b�g����B
	void ResetBuff(int i);

	bool AddATB();			//�A�N�e�B�u�^�C�������Z����B

	/// <summary>
	///�X�e�[�g�̍X�V�����B 
	/// </summary>
	void StateUpdate();

private:
	//	�X�e�[�^�X
	Status m_statusBase;								//��b�X�e�[�^�X�B
	Status m_status;									//�X�e�[�^�X�B
	MonsterState m_stateAI = en_state_Good;						//�X�e�[�g�B
	bool m_IsDeath = false;								//�L�����N�^�[���S�t���O�B
	const float addTime = 1.0f / 144.0f * 4.0f;			//���Z�^�C���B
	float m_activeTime = 0.0f;							//�A�N�e�B�u�^�C���B
	float m_coolTime = 30.0f;							//�N�[���^�C���B
	float buffTimeList[en_buff_num] = { 0.0f };			//�o�t�^�C���B

	StatusUI* m_UI = nullptr;
};

