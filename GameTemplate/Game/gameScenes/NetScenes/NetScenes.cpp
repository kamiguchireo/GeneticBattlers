#include "stdafx.h"
#include "NetScenes.h"
#include "Network/SampleNetwork.h"
#include "Fade.h"
#include "NetSceneText.h"

//行動テーブルのデータ。
//!<skillNo		スキル番号。
//!<target		ターゲット番号。
//!<rate		使用頻度。
struct AIData {
	int skillNo = 0;
	int target = 0;
	float rate = 0.0f;
};

NetScenes* NetScenes::m_instance = nullptr;

NetScenes::NetScenes()
{
	if (m_instance != nullptr) {
		std::abort();
	}
	m_instance = this;

	//ひとまずリストのサイズを3にする。
	m_Tabelelist.resize(3);
}

NetScenes::~NetScenes()
{
	m_instance = nullptr;
	DeleteGO(m_text);
}

bool NetScenes::Start()
{
	//ネットの処理。
	m_net = SampleNetwork::GetInstance();
	m_net->JoinRoom();

	//フェードの処理。
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	//テキストのインスタンス化
	m_text = NewGO<NetSceneText>(0);

	return true;
}

void NetScenes::Update()
{
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_net->putEvent(1, enAI_Attaker);
		SendAIData("Assets/AIData/Attaker.bin");
		m_net->putEvent(1, enAI_Healer);
		SendAIData("Assets/AIData/Healer.bin");
		m_net->putEvent(1, enAI_Supporter);
		SendAIData("Assets/AIData/Supporter.bin");
	}
	else if (g_pad[0].IsTrigger(enButtonB)) {
		AIDataTable hoge = *m_Tabelelist.begin();
	}
}

void NetScenes::PushBackData(int ListNum, int skill, int target, float rate)
{
	if (m_instance == nullptr) { return; }

	AIData hoge = { skill,target,rate };
	m_Tabelelist[ListNum].push_back(hoge);
}

void NetScenes::SendAIData(const char* filePath)
{
	FILE* fp;
	fp = fopen(filePath, "rb");

	if (fp == nullptr)	return;

	AIData hoge;
	std::vector<AIData> dataList;

	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		dataList.push_back(hoge);
	}

	fclose(fp);

	//これで送れるのか？
	for (auto& data : dataList) {
		//m_net->putEvent(1, 0);
		m_net->putEvent(2, data.skillNo);
		m_net->putEvent(3, data.target);
		m_net->putEvent(4, data.rate);

		m_net->SendEventHash();
	}

}
