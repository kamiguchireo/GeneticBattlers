#pragma once
#include "monster/MonsterData.h"

namespace GA {
	enum Job
	{
		en_Attacker,
		en_Healer,
		en_Supporter,
		en_JobNum
	};

	typedef std::vector<AIData> AITable;		//AI情報。
	typedef std::vector<AITable> AITableList;	//AI情報テーブル。
	struct Genetic
	{
		AITableList genetic;		//遺伝子となるAI情報テーブル。
		int winRate = 0;			//評価値となる勝率(%)。
	};
	typedef std::vector<Genetic> GeneticsList;//AI情報テーブルで構成される遺伝子情報。さすがにこれは深すぎるかなぁ？
}

class EvaluationCalculator;
class Fade;

class GAScenes:public IGameObject
{
public:
	GAScenes();
	~GAScenes();
	bool Start()override;
	void Update()override;
private:
	//データを読み込む。
	void LoadAIData(const char* filePath, GA::AITable& ai);
	//初期遺伝子を作成する。
	void FirstGenesCreate();
	//勝率を測定。
	void CalcWinRate();
	//評価値でソートを行う。
	void SortGenes();
	//淘汰の処理。
	void GeneSelection(); 
	//交叉の処理。
	void GenesCrossover();
	//確率を交叉させる。。
	void GeneSwap(GA::AITable& _t1, GA::AITable& _t2);
	//突然変異の処理。
	void Mutation();
	//AIの確率を変動させる
	void GeneMutation(GA::AITable & _table);

	/// <summary>
	/// １．勝率の測定処理。つまりは戦闘処理を行うクラスが必要なのでは...
	///		ここで遺伝子を確率に直しておかないとですねぇ
	///		んで計測結果を記録する関数と評価値でソートする関数が必要ですねぇ 終わりかなぁ
	/// ２．交叉の処理。
	/// ３．突然変異の処理。
	/// </summary>


private:		//定数。
	static const float RATE_CHANGE;		//初期遺伝子生成時の確率変動幅
	static const int CHANGE_NUM;		//確率変動で作る数。
	const int SELECT_ELETE = 20;		//選択するエリートの数。
	const int MAX_GENERATION = 50;		//繰り返す世代数。
	const float MUTATION_RATE = 0.05;	//突然変異の確率。

	enum Scene {
		en_FadeIn,
		en_FirstGeneric,
		en_GA,
		en_End,
		en_FadeOut
	};

private:		//メンバ変数。
	prefab::SpriteRender* m_sprite = nullptr;			//背景画像。
	prefab::FontRender* m_fontGeneration = nullptr;		//フォント
	prefab::FontRender* m_fontWinRate = nullptr;		//フォント
	Fade* m_fade = nullptr;		//フェードクラス。
	Scene m_sceneState = en_FadeIn;

	EvaluationCalculator* m_evaluationCalc = nullptr;
	GA::AITable m_myAI[GA::en_JobNum];		//元となるAIのデータ。
	GA::AITable m_enemyAI[GA::en_JobNum];	//敵のAIデータ。
	GA::GeneticsList m_currentGenetics;	//現行世代の遺伝子。
	GA::GeneticsList m_eliteGenetics;		//エリート遺伝子のリスト。
	int m_geneSize = 0;		//遺伝子のサイズ。
	int m_currentGenerationNum = 0;		//世代数。
	int m_maxWinRate = 0;		//最高遺伝子の勝率。
};

