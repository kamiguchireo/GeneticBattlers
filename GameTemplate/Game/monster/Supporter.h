#pragma once
#include "MonsterBase.h"
class Supporter :public MonsterBase
{
public:
	Supporter();
	~Supporter();

	bool Start();
	void Update();
	bool BattleAction();
	////スキル選択。
	//void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team) override;

	//AIデータを読み込みたい。
	void Init(const char* filePath);
	//AIデータを書き込みたい。
	virtual void Save(const char* filePath);
};

