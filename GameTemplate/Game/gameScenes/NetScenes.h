#pragma once
class NetScenes:public IGameObject
{
public:
	NetScenes();
	~NetScenes();
	bool Start();
	void Update();

private:
	//��ԁB
	enum NetState {
		enState_Init,
		enState_Idle,
		enState_Exit
	};
	NetState m_state = enState_Idle;	//�X�e�[�g�B
};

