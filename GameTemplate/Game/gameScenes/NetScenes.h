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

	static NetScenes* GetInstance()
	{
		return m_instance;
	}

	void PushBackData(int data)
	{
		intData.push_back(data);
	}
	void PushBackData(float data)
	{
		floatData.push_back(data);
	}

private:
	void SendData(const char* filePath);

	static NetScenes* m_instance;	//インスタンス。

	//状態。
	enum NetState {
		enState_Init,
		enState_Idle,
		enState_Exit
	};
	NetState m_state = enState_Idle;	//ステート。
	SampleNetwork* m_net = nullptr;			//ネットワーク。
	Fade* m_fade = nullptr;					//フェードのポインタ。

	prefab::FontRender* m_fontRender = nullptr;			//フォントレンダー。
	std::unique_ptr<DirectX::SpriteFont> m_spFont;		//スプライトフォントデータ。
	CVector3 m_color = CVector3::One();					//フォントの色。

	std::vector<int> intData;
	std::vector<float> floatData;
};

