#pragma once
#include "parameter/AISimpleManager.h"
#include "parameter/StatusSimpleManager.h"

/// <summary>
/// GA�p�̃����X�^�[�f�[�^�Ǘ��N���X
/// </summary>

class MonsterData
{
public:
	MonsterData();
	~MonsterData();

	AISimpleManager& GetAIManager()
	{
		return m_AImanager;
	}

	StatusSimpleManager* GetStatusManager()
	{
		return &m_statusManager;
	}

private:
	AISimpleManager m_AImanager;
	StatusSimpleManager m_statusManager;
};

