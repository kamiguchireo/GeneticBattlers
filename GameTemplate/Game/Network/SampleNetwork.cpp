#include "stdafx.h"
#include "SampleNetwork.h"

SampleNetwork::SampleNetwork(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
	:mLoadBalancingClient(mListener, appID, appVersion)
{
}

void SampleNetwork::connect(void)
{

	if (!mLoadBalancingClient.connect())
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"connect");

	}
}

//1�b��10�`20��ǂ�ł�������
void SampleNetwork::run(void)
{
	if (!shouldExit)
	{
		//������Ă΂Ȃ�����A�l�b�g���[�N�͑S����������܂���
		mLoadBalancingClient.service();
	}
}

//�A�v���P�[�V�������I������Ƃ���
//���[�U�[�����O�A�E�g����Ƃ��ɕK���Ă�ł�������
void SampleNetwork::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}
