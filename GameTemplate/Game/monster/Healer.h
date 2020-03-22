#pragma once
#include "MonsterBase.h"
class Healer :public MonsterBase
{
public:
	Healer();
	~Healer();

	bool Start();
	void Update();
	bool BattleAction();
	//スキル選択。
	void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team) override;
	//AIデータを読み込みたい。
	void Init(const wchar_t* filePath);
};

