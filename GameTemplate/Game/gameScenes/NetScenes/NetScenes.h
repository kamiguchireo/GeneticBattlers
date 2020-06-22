#pragma once

class Fade;
class SampleNetwork;
class NetSceneText;

struct AIData;

//��ԁB
enum NetState {
	enState_Idle,		//�ʐM�ҋ@��ԁB
	enState_SendGI,		//GI�̑��M�B
	enState_SendStatus,	//�X�e�[�^�X�̑��M�B
	enState_Exit,		//�ʐM�I���B
	enState_Brake,		//�ʐM�̒��f�B
	enState_FadeOut,	//�t�F�[�h�A�E�g����B
	enState_Battle,		//�퓬�V�[���Ɉڍs�����B
	enState_Error		//�ʐM�G���[�B
};

class NetScenes:public IGameObject
{
public:
	NetScenes();
	~NetScenes();
	bool Start();
	void Update();
	//�C���X�^���X�擾�B
	static NetScenes* GetInstance()
	{
		return m_instance;
	}
	//�C�x���g�؂�ւ��B
	void SwitchEvent(int type);
	void SwitchError();

	/// <summary>
	/// �s���e�[�u�����v�b�V���o�b�N����B
	/// </summary>
	/// <param name="ListNum">�N�̍s�����X�g���̋�ʁB</param>
	/// <param name="skill">�X�L��</param>
	/// <param name="target">�^�[�Q�b�g</param>
	/// <param name="rate">�m��</param>
	void PushBackData(int ListNum, int skill, int target, float rate);
	/// <summary>
	/// �f�[�^�����𑗂�B
	/// </summary>
	void SendData();
	//�X�e�[�g�̕ύX�B
	void SetStateIdle();		//�ҋ@��ԁB
	void SetStateSendGI();		//GI�f�[�^�𑗂�B
	void SetStateSendStatus();	//�X�e�[�^�X�f�[�^�𑗂�B

	typedef std::vector<AIData> AIDataTable;			//�s���e�[�u���B
	//�A�^�b�J�[�̃f�[�^���擾�B
	const AIDataTable& GetAttakerData()const
	{
		return m_Tabelelist[enAI_Attaker];
	}
	//�q�[���[�̃f�[�^���擾�B
	const AIDataTable& GetHealerData()const
	{
		return m_Tabelelist[enAI_Healer];
	}
	//�A�^�b�J�[�̃f�[�^���擾�B
	const AIDataTable& GetSupporterData()const
	{
		return m_Tabelelist[enAI_Supporter];
	}

private:
	/// <summary>
	/// AI�f�[�^�𑗂�B
	/// </summary>
	/// <param name="filePath">����f�[�^�̃t�@�C���p�X�B</param>
	void SendAIData(const char* filePath,int dataType);
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

	std::vector<AIDataTable> m_Tabelelist;				//�s���e�[�u���̃��X�g�B
	NetSceneText* m_text = nullptr;						//�e�L�X�g�Ǘ��p�N���X�B
};

