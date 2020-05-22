#pragma once

class Fade;
class SampleNetwork;
class NetSceneText;

struct AIData;

class NetScenes:public IGameObject
{
public:
	NetScenes();
	~NetScenes();
	bool Start();
	void Update();

	static NetScenes* GetInstance()
	{
		return m_instance;
	}

	/// <summary>
	/// �s���e�[�u�����v�b�V���o�b�N����B
	/// </summary>
	/// <param name="ListNum">�N�̍s�����X�g���̋�ʁB</param>
	/// <param name="skill">�X�L��</param>
	/// <param name="target">�^�[�Q�b�g</param>
	/// <param name="rate">�m��</param>
	void PushBackData(int ListNum, int skill, int target, float rate);

private:
	/// <summary>
	/// AI�f�[�^�𑗂�B
	/// </summary>
	/// <param name="filePath">����f�[�^�̃t�@�C���p�X�B</param>
	void SendAIData(const char* filePath);
	//����f�[�^�̎�ނ̔��ʁB
	enum EnSendData {
		enAI_Attaker,
		enAI_Healer,
		enAI_Supporter,
		enSta_Attaker,
		enSta_Healer,
		enSta_Supporter
	};

	static NetScenes* m_instance;	//�C���X�^���X�B

	//��ԁB
	enum NetState {
		enState_Init,
		enState_Idle,
		enState_Exit
	};
	NetState m_state = enState_Idle;	//�X�e�[�g�B
	SampleNetwork* m_net = nullptr;			//�l�b�g���[�N�B
	Fade* m_fade = nullptr;					//�t�F�[�h�̃|�C���^�B

	typedef std::vector<AIData> AIDataTable;			//�s���e�[�u���B
	std::vector<AIDataTable> m_Tabelelist;				//�s���e�[�u���̃��X�g�B
	NetSceneText* m_text = nullptr;
};

