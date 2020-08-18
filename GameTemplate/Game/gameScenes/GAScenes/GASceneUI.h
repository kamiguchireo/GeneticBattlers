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
	void SetWinRate(int generation, int maxR, float aveR);

	/// <summary>
	/// 最終的な勝率。
	/// </summary>
	/// <param name="maxR">最大勝率。</param>
	/// <param name="aveR">平均勝率。</param>
	void EndWinRate(int maxR, float aveR);

private:
	prefab::SpriteRender* m_sprite = nullptr;			//背景画像。
	prefab::SpriteRender* m_gauge = nullptr;			//ゲージ
	prefab::SpriteRender* m_meter = nullptr;			//メーター
	prefab::FontRender* m_fontGeneration = nullptr;		//フォント
	prefab::FontRender* m_fontWinRate = nullptr;		//フォント

	int m_currentGenerationNum = 0;		//世代数。
	int m_maxWinRate = 0;		//最高遺伝子の勝率(%)。
	float m_aveWinRate = 0.0f;	//現行世代の平均勝率(%)。
	float m_currentProgress = 0.0f;	//現行世代の評価計算率。
};

