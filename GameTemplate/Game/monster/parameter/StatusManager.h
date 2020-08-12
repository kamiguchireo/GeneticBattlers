#pragma once
#include "StatusBase.h"

class StatusUI;


//ステータスを管理するクラス。
class StatusManager : public CStatusBase
{
public:
	StatusManager() {};
	~StatusManager() {};

	void SetUI(StatusUI* UI)
	{
		m_UI = UI;
	}

	bool AddATB()override;

	/// <summary>
	/// ステートの更新処理。
	/// </summary>
	/// <param name="ui"></param>
	void StateUpdate()override;

private:
	StatusUI* m_UI = nullptr;
};

