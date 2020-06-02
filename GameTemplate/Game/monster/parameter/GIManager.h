#pragma once

//�s���e�[�u���̃f�[�^�B
//!<skillNo		�X�L���ԍ��B
//!<target		�^�[�Q�b�g�ԍ��B
//!<rate		�g�p�p�x�B
struct AIData {
	int skillNo = 0;
	int target = 0;
	float rate = 0.0f;
};

struct ResultData {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
};

class GIManager
{
public:
	GIManager();
	~GIManager();
	/// <summary>
	/// �t�@�C���p�X����GI�����[�h����B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	bool Load(const char* filePath);
	/// <summary>
	/// �f�t�H���g�̃f�[�^�����[�h����Ƃ��Ɏg���B
	/// </summary>
	/// <param name="filePath">�f�t�H���g�̐��l�̓������t�@�C���p�X�B</param>
	void LoadDefault(const char* filePath);
	/// <summary>
	/// GI���L�^����B
	/// </summary>
	void Save();
	/// <summary>
	/// GI�̍X�V���s���B
	/// </summary>
	void GIUpdate();
	/// <summary>
	/// �s���𗐐��Ō��肷��B
	/// </summary>
	/// <param name="skill">���肵���X�L�����擾����B</param>
	/// <param name="target">���肵���^�[�Q�b�g���擾����B</param>
	void ActionDicide(int* skill, int* target);
	/// <summary>
	/// �s���̃��U���g��ςށB
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	/// <param name="skill">�g�p�X�L���B</param>
	/// <param name="target">�^�[�Q�b�g�B</param>
	void PushBackResult(int damage, int skill, int target)
	{
		ResultData res = { damage,skill,target };
		m_actResList.push_back(res);
	}

private:
	//	AI�f�[�^�B
	std::vector<AIData> m_AI;							//AI�f�[�^�B
	char m_AIPath[128];									//AI�f�[�^�̃t�@�C���p�X�B
	std::vector<ResultData> m_actResList;				//�s���̃��U���g�̉ϒ��z��B
};
