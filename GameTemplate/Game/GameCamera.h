#pragma once
class GameCamera:public IGameObject
{
public:
	GameCamera();		//�R���X�g���N�^�B
	~GameCamera();		//�f�X�g���N�^�B
	
	bool Start();		//�����������B
	void Update();		//�X�V�����B

	//�V���O���g���p�^�[���B
	static GameCamera* GetInstance()
	{
		return m_instance;
	}

private:
	static GameCamera* m_instance;		//�V���O���g���p�^�[���B
	CVector3 m_firstPosition = CVector3::Zero();
	CVector3 m_firstTarget = CVector3::Zero();
};

