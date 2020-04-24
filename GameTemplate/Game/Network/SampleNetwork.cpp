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

//1秒に10～20回読んでください
void SampleNetwork::run(void)
{
	if (!shouldExit)
	{
		//これを呼ばない限り、ネットワークは全く処理されません
		mLoadBalancingClient.service();
	}
}

//アプリケーションを終了するときや
//ユーザーがログアウトするときに必ず呼んでください
void SampleNetwork::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}
