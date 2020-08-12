#pragma once
#include "StatusBase.h"

class StatusUI;


//�X�e�[�^�X���Ǘ�����N���X�B
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
	/// �X�e�[�g�̍X�V�����B
	/// </summary>
	/// <param name="ui"></param>
	void StateUpdate()override;

private:
	StatusUI* m_UI = nullptr;
};

