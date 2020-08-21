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

	//状態更新。
	void StateUpdate() override;

	//ステータスを元に戻す。
	void ResetStatus();

private:

};

