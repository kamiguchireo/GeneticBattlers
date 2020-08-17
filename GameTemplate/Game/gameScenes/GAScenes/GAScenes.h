#pragma once
#include "monster/MonsterData.h"


typedef std::vector<AIData> AITable;		//AI情報。
typedef std::vector<AITable> AITableList;	//AI情報テーブル。
typedef std::vector<AITableList> AIGenetics;//AI情報テーブルで構成される遺伝子情報。さすがにこれは深すぎるかなぁ？

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

	/// <summary>
	/// １．勝率の測定処理。つまりは戦闘処理を行うクラスが必要なのでは...
	///		ここで遺伝子を確率に直しておかないとですねぇ
	/// ２．交叉の処理。
	/// ３．突然変異の処理。
	/// </summary>


	static const int GENETICS_NUM = 100;
	static const float RATE_CHANGE;		//初期遺伝子生成時の確率変動幅
	static const int CHANGE_NUM;		//確率変動で作る数。
	enum Job
	{
		en_Attacker,
		en_Healer,
		en_Supporter,
		en_JobNum
	};

	prefab::SpriteRender* m_sprite = nullptr;
	prefab::FontRender* m_font = nullptr;
	AITable m_myAI[en_JobNum];		//元となるAIのデータ。
	AITable m_enemyAI[en_JobNum];	//敵のAIデータ。
	AIGenetics m_currentGenetics;	//現行世代の遺伝子。
	//AITableList m_currentGenetics[en_JobNum];	//現行世代の遺伝子。
	std::vector<int> m_winRate;				//勝率。
	int m_actionNum = 0;		//遺伝子の構成データ数。
};

