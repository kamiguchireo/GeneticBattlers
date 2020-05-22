#pragma once

class Fade;
class SampleNetwork;
class NetSceneText;

struct AIData;

//��ԁB
enum NetState {
	enState_Init,
	enState_Idle,
	enState_Send,
	enState_Exit
};

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
	/// <summary>
	/// �f�[�^�𑗂�B
	/// </summary>
	void SendData();
	//�X�e�[�g�̕ύX�B
	void SetStateIdle();
	void SetStateSend();

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

	NetState m_state = enState_Idle;	//�X�e�[�g�B

	SampleNetwork* m_net = nullptr;			//�l�b�g���[�N�B
	Fade* m_fade = nullptr;					//�t�F�[�h�̃|�C���^�B

	typedef std::vector<AIData> AIDataTable;			//�s���e�[�u���B
	std::vector<AIDataTable> m_Tabelelist;				//�s���e�[�u���̃��X�g�B
	NetSceneText* m_text = nullptr;						//�e�L�X�g�Ǘ��p�N���X�B
};

