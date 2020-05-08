#pragma once
#include "SourceFile/graphic/font/FontRender.h"

class Fade;
class SampleNetwork;

class NetScenes:public IGameObject
{
public:
	NetScenes();
	~NetScenes();
	bool Start();
	void Update();

private:
	void SendData(const char* filePath);

	//��ԁB
	enum NetState {
		enState_Init,
		enState_Idle,
		enState_Exit
	};
	NetState m_state = enState_Idle;	//�X�e�[�g�B
	SampleNetwork* m_net = nullptr;			//�l�b�g���[�N�B
	Fade* m_fade = nullptr;					//�t�F�[�h�̃|�C���^�B

	prefab::FontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B
	std::unique_ptr<DirectX::SpriteFont> m_spFont;		//�X�v���C�g�t�H���g�f�[�^�B
	CVector3 m_color = CVector3::One();					//�t�H���g�̐F�B
};

