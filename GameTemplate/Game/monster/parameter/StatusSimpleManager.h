#pragma once
#include "StatusBase.h"

/// <summary>
/// GA���񂷂��߂̊ȈՃX�e�[�^�X�Ǘ��N���X�B
/// </summary>

class StatusSimpleManager :public CStatusBase
{
public:
	StatusSimpleManager();
	~StatusSimpleManager();

	//�A�N�e�B�u�^�C����i�߂�B
	bool AddATB() override;

	//��ԍX�V�B
	void StateUpdate() override;

	//�X�e�[�^�X�����ɖ߂��B
	void ResetStatus();

private:

};

