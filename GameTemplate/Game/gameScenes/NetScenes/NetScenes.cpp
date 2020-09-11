#include "stdafx.h"
#include "NetScenes.h"
#include "Network/SampleNetwork.h"
#include "Fade.h"
#include "NetSceneText.h"
#include "../TitleScene.h"
#include "../BattleScenes/BattleScenes.h"

NetScenes* NetScenes::m_instance = nullptr;

NetScenes::NetScenes()
{
	if (m_instance != nullptr) {
		std::abort();
	}
	m_instance = this;

	//�ЂƂ܂����X�g�̃T�C�Y��3�ɂ���B
	m_Tabelelist.resize(3);
	//�e�L�X�g�̃C���X�^���X��
	m_text = NewGO<NetSceneText>(0);
}

NetScenes::~NetScenes()
{
	m_instance = nullptr;
	DeleteGO(m_text);
	DeleteGO(m_spriteRender);
}

bool NetScenes::Start()
{
	//�l�b�g�̏����B
	m_net = SampleNetwork::GetInstance();
	m_net->JoinRoom("aaa", 2);

	m_spriteRender = NewGO<prefab::SpriteRender>(0);
	m_spriteRender->Init(
		L"Assets/sprite/BackWindow.dds",
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

	//�t�F�[�h�̏����B
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();


	SetStateIdle();

	return true;
}

void NetScenes::Update()
{
	switch (m_state)
	{
	case enState_Idle:
		//B�{�^���Ń^�C�g���ɖ߂�B
		if (g_pad[0].IsTrigger(enButtonB))
		{
			m_state = enState_Brake;
			m_fade->StartFadeOut();
		}
		else {
			m_net->SendEvent(enState_SendGI);
		}
		break;

	case enState_SendGI:
		m_net->SendEvent(enState_Exit);				//�C�x���g�؂�ւ��B
		break;

	case enState_Exit:
		//A�{�^���Ő퓬�Ɉڂ�B
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_state = enState_SceneChange;
			m_fade->StartFadeOut();
		}
		break;

	case enState_Brake:
		if (!m_fade->IsFade()) {
			DeleteGO(this);
			NewGO<TitleScene>(0);
			m_net->LeaveRoom();
		}
		break;

	case enState_SceneChange:
		if (!m_fade->IsFade()) {
			//�퓬�V�[���Ɉڍs����B
			DeleteGO(m_text);			//�e�L�X�g�폜�B
			m_text = nullptr;			//�|�C���^��null������B
			DeleteGO(m_spriteRender);	//�X�v���C�g�폜�B
			m_spriteRender = nullptr;	//null������B

			NewGO<BattleScenes>(0);		//�퓬�V�[�����쐬�B
			m_state = enState_Battle;
		}
		break;

	case enState_Error:
		//B�{�^���Ń^�C�g���ɖ߂�B
		if (g_pad[0].IsTrigger(enButtonB))
		{
			m_state = enState_Brake;
			m_fade->StartFadeOut();
		}
		break;

	case enState_Battle:
		break;
	default:
		break;
	}
}

void NetScenes::SwitchEvent(int type)
{
	switch (type)
	{
	case enState_Idle:
		break;

	case enState_SendGI:
		if (m_state == enState_Idle) {					//���݃X�e�[�g���Ӑ}���ĂȂ��Ƃ��͖����B
			SetStateSendGI();		//GI�f�[�^�̑��M�B
		}
		break;

	case enState_Exit:
		if (m_state != enState_SendGI) return;		//���݃X�e�[�g���Ӑ}���ĂȂ��Ƃ��͖����B
		m_state = enState_Exit;
		if (m_text != nullptr)
		{
			m_text->SetState(m_state);
		}
		break;

	case enState_Brake:
		break;

	default:
		break;
	}
}

void NetScenes::SwitchError()
{
	if (m_state == enState_Exit || m_state == enState_Battle) return;
	m_state = enState_Error;
	if (m_text != nullptr) {
		m_text->SetState(m_state);
	}
}

void NetScenes::PushBackData(int ListNum, int skill, int target, float rate)
{
	AIData hoge = { skill,target,rate };
	m_Tabelelist[ListNum].push_back(hoge);
}

void NetScenes::SendData()
{
	SendAIData("Assets/AIData/Attacker.bin", enAI_Attaker);
	SendAIData("Assets/AIData/Healer.bin", enAI_Healer);
	SendAIData("Assets/AIData/Supporter.bin", enAI_Supporter);
}

void NetScenes::SetStateIdle()
{
	m_state = enState_Idle;
	if (m_text != nullptr)
	{
		m_text->SetState(m_state);
	}
}

void NetScenes::SetStateSendGI()
{
	SendData();
	m_state = enState_SendGI;
	if (m_text != nullptr)
	{
		m_text->SetState(m_state);
	}
}

void NetScenes::SendAIData(const char* filePath, int dataType)
{
	FILE* fp;
	fp = fopen(filePath, "rb");

	if (fp == nullptr)
	{
		fp = fopen("Assets/AIData/DefaultData/DataDefault.bin", "rb");
		if (fp == nullptr)
		{
			return;
		}
	}

	AIData hoge;
	std::vector<AIData> dataList;

	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		dataList.push_back(hoge);
	}

	fclose(fp);

	//�f�[�^�𑗐M���Ă����B
	for (auto& data : dataList) {
		m_net->putEvent(1, dataType);
		m_net->putEvent(2, data.skillNo);
		m_net->putEvent(3, data.target);
		m_net->putEvent(4, data.rate);

		m_net->SendEventHash();
	}

}
