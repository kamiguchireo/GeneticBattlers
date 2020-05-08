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
};

