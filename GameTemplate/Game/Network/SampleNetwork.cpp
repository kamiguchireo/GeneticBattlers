#include "stdafx.h"
//#include "SampleNetwork.h"
//
//SampleNetwork::SampleNetwork(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
//	:m_LoadBalancingClient(m_Listener,appID,appVersion)
//{
//
//}
//
//void SampleNetwork::connect(void)
//{
//	if (!m_LoadBalancingClient.connect())
//	{
//		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"接続できませんでしたぁぁ！！");
//
//	}
//}
//
//void main(void)
//{
//	static const ExitGames::Common::JString appID = L"<no-app-id>";
//	static const ExitGames::Common::JString appVersion = L"1.0";
//
//	SampleNetwork networkLogic(appID, appVersion);
//	networkLogic.connect();
//}