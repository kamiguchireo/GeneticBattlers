#pragma once

class Fade;
class SampleNetwork;
class NetSceneText;

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
	/// <summary>
	/// AIデータを送る。
	/// </summary>
	/// <param name="filePath">送るデータのファイルパス。</param>
	void SendAIData(const char* filePath);
	//送るデータの種類の判別。
	enum EnSendData {
		enAI_Attaker,
		enAI_Healer,
		enAI_Supporter,
		enSta_Attaker,
		enSta_Healer,
		enSta_Supporter
	};

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

	typedef std::vector<AIData> AIDataTable;			//行動テーブル。
	std::vector<AIDataTable> m_Tabelelist;				//行動テーブルのリスト。
	NetSceneText* m_text = nullptr;
};

