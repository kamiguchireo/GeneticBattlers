#pragma once
#include "StatusBase.h"

/// <summary>
/// GAを回すための簡易ステータス管理クラス。
/// </summary>

class StatusSimpleManager :public CStatusBase
{
public:
	StatusSimpleManager();
	~StatusSimpleManager();

	//アクティブタイムを進める。
	bool AddATB() override;

	void StateUpdate() override;

private:

};

