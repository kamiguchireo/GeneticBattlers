#pragma once

class Fade;
class SampleNetwork;
class NetSceneText;

struct AIData;

//状態。
enum NetState {
	enState_Init,
	enState_Idle,
	enState_Send,
	enState_Exit
};

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
	/// <summary>
	/// データたちを送る。
	/// </summary>
	void SendData();
	//ステートの変更。
	void SetStateIdle();
	void SetStateSend();

	typedef std::vector<AIData> AIDataTable;			//行動テーブル。
	//アタッカーのデータを取得。
	const AIDataTable& GetAttakerData()const
	{
		return m_Tabelelist[enAI_Attaker];
	}
	//ヒーラーのデータを取得。
	const AIDataTable& GetHealerData()const
	{
		return m_Tabelelist[enAI_Healer];
	}
	//アタッカーのデータを取得。
	const AIDataTable& GetSupporterData()const
	{
		return m_Tabelelist[enAI_Supporter];
	}

private:
	/// <summary>
	/// AIデータを送る。
	/// </summary>
	/// <param name="filePath">送るデータのファイルパス。</param>
	void SendAIData(const char* filePath,int dataType);
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

	NetState m_state = enState_Idle;	//ステート。

	SampleNetwork* m_net = nullptr;			//ネットワーク。
	Fade* m_fade = nullptr;					//フェードのポインタ。

	std::vector<AIDataTable> m_Tabelelist;				//行動テーブルのリスト。
	NetSceneText* m_text = nullptr;						//テキスト管理用クラス。
};

