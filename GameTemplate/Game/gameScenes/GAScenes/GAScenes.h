#pragma once
#include "monster/MonsterData.h"

enum Job
{
	en_Attacker,
	en_Healer,
	en_Supporter,
	en_JobNum
};

class EvaluationCalculator;

typedef std::vector<AIData> AITable;		//AI情報。
typedef std::vector<AITable> AITableList;	//AI情報テーブル。
struct Genetic
{
	AITableList genetic;		//遺伝子となるAI情報テーブル。
	int winRate = 0;			//評価値となる勝率(%)。
};
typedef std::vector<Genetic> AIGenetics;//AI情報テーブルで構成される遺伝子情報。さすがにこれは深すぎるかなぁ？

class GAScenes:public IGameObject
{
public:
	GAScenes();
	~GAScenes();
	bool Start()override;
	void Update()override;
private:
	//データを読み込む。
	void LoadAIData(const char* filePath, AITable& ai);
	//初期遺伝子を作成する。
	void FirstGenesCreate();
	//勝率を測定。
	void CalcWinRate();
	//評価値でソートを行う。
	void SortGenes();

	/// <summary>
	/// １．勝率の測定処理。つまりは戦闘処理を行うクラスが必要なのでは...
	///		ここで遺伝子を確率に直しておかないとですねぇ
	///		んで計測結果を記録する関数と評価値でソートする関数が必要ですねぇ 終わりかなぁ
	/// ２．交叉の処理。
	/// ３．突然変異の処理。
	/// </summary>


	static const int GENETICS_NUM = 100;
	static const float RATE_CHANGE;		//初期遺伝子生成時の確率変動幅
	static const int CHANGE_NUM;		//確率変動で作る数。

	prefab::SpriteRender* m_sprite = nullptr;
	prefab::FontRender* m_font = nullptr;
	EvaluationCalculator* m_evaluationCalc = nullptr;
	AITable m_myAI[en_JobNum];		//元となるAIのデータ。
	AITable m_enemyAI[en_JobNum];	//敵のAIデータ。
	AIGenetics m_currentGenetics;	//現行世代の遺伝子。
	int m_actionNum = 0;		//遺伝子の構成データ数。
};

