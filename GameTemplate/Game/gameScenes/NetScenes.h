#pragma once
#include "SourceFile/graphic/font/FontRender.h"

class Fade;
class SampleNetwork;

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
	/// 行動テーブルをプッシュバックする。
	/// </summary>
	/// <param name="ListNum">誰の行動リストかの区別。</param>
	/// <param name="skill">スキル</param>
	/// <param name="target">ターゲット</param>
	/// <param name="rate">確率</param>
	void PushBackData(int ListNum, int skill, int target, float rate);

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

	typedef std::vector<AIData> AIDataTable;			//行動テーブル。
	std::vector<AIDataTable> m_Tabelelist;				//行動テーブルのリスト。
};

