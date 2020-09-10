#pragma once
#include "monster/parameter/AIBase.h"

/// <summary>
/// 敵のAI情報を保持しておく。
/// </summary>

class AIResouce:public IGameObject
{
public:
	AIResouce();
	~AIResouce();

	static AIResouce* GetInstance()
	{
		return m_instance;
	}

	//アタッカーの情報を保存。
	void SetAttaker(const std::vector<AIData>& attacker)
	{
		m_attacker = attacker;
	}
	//ヒーラーの情報を保存。
	void SetHealer(const std::vector<AIData>& healer)
	{
		m_healer = healer;
	}
	//サポーターの情報を保存。
	void SetSupporter(const std::vector<AIData>& supporter)
	{
		m_supporter = supporter;
	}
	//アタッカーの情報取得。
	std::vector<AIData>& GetAttacker()
	{
		return m_attacker;
	}
	//ヒーラーの情報取得。
	std::vector<AIData>& GetHealer()
	{
		return m_healer;
	}
	//サポーターの情報取得。
	std::vector<AIData>& GetSupporter()
	{
		return m_supporter;
	}

	//データをクリア。
	void ClearData();

private:
	static AIResouce* m_instance;			//インスタンス。

	std::vector<AIData> m_attacker;			//アタッカー情報
	std::vector<AIData> m_healer;			//ヒーラー情報
	std::vector<AIData> m_supporter;		//サポーター情報
};

