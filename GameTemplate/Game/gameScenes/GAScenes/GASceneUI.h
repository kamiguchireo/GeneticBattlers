#pragma once
class GASceneUI : public IGameObject
{
public:
	GASceneUI();
	~GASceneUI();
	bool Start();
	void Update();
	/// <summary>
	/// 現在の世代数と勝率をセット。
	/// </summary>
	/// <param name="generation">現行世代</param>
	/// <param name="maxR">最大勝率</param>
	/// <param name="aveR">平均勝率</param>
	void SetWinRate(const int generation, const int maxR, const float aveR);

	/// <summary>
	/// 最終的な勝率。
	/// </summary>
	/// <param name="maxR">最大勝率。</param>
	/// <param name="aveR">平均勝率。</param>
	void EndWinRate(const int maxR, const float aveR);

	//最終世代数を設定。
	void SetEndGeneration(const int gene)
	{
		m_endGenerationNum = gene;
	}


private:		//定数。
	const float GRAPH_W = 640.0f;
	const float GRAPH_H = 360.0f;
	float m_wideRange = 0.0f;		//一世代ごとの横の間隔。

private:
	prefab::SpriteRender* m_sprite = nullptr;			//背景画像。
	prefab::SpriteRender* m_graph = nullptr;			//ゲージ
	prefab::SpriteRender* m_maxWinLine = nullptr;			//最大勝率スプライト
	prefab::SpriteRender* m_aveWinLine = nullptr;			//平均勝率スプライト
	std::list<prefab::SpriteRender*> m_maxWinLineList;		//最大勝率折れ線グラフ
	std::list<prefab::SpriteRender*> m_aveWinLineList;		//平均勝率折れ線グラフ
	prefab::FontRender* m_fontGeneration = nullptr;		//フォント
	prefab::FontRender* m_fontWinRate = nullptr;		//フォント

	int m_currentGenerationNum = 0;		//世代数。
	int m_endGenerationNum = 0;			//最大世代数。
	int m_maxWinRate = 0;		//最高遺伝子の勝率(%)。
	float m_aveWinRate = 0.0f;	//現行世代の平均勝率(%)。
	float m_currentProgress = 0.0f;	//現行世代の評価計算率。
};

