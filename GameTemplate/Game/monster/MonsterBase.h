#pragma once

/// <summary>
/// �X�e�[�^�X�̍\���́B
/// </summary>
/// <remarks>
/// ���@�U���͂�INT����int�^�ƊԈႦ����������MAT�Ƃ����B
/// </remarks>
struct Status {
	int HP;
	int MP;
	int ATK;
	int DEF;
	int MAT;
	int MDF;
	int DEX;
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
	MonsterBase();
	~MonsterBase();
	
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
	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	void Damage(int damage)
	{
		m_status.HP -= damage;
	}
	/// <summary>
	/// MP���g���B
	/// </summary>
	/// <param name="mp">����MP�ʁB</param>
	void UseMP(int mp)
	{
		m_status.MP -= mp;
	}
	

protected:
	SkinModel* m_model = nullptr;
	CVector3 m_position = CVector3::Zero();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	Status m_status;									//�X�e�[�^�X�B
	bool m_isDeath = false;								//�퓬�s�\�t���O�B
	int m_stateAI = 0;									//�X�e�[�g�B
};
