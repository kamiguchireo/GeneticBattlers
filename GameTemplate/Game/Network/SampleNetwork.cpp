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
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"接続できませんでしたぁぁ！！");

	}
}

//1秒に10～20回読んでください
void SampleNetwork::run(void)
{
	//これを呼ばない限り、ネットワークは全く処理されません
	mLoadBalancingClient.service();
}

//アプリケーションを終了するときや
//ユーザーがログアウトするときに必ず呼んでください
void SampleNetwork::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

//void main(void)
//{
//	//ここに作ったapp idをセットする
//	static const ExitGames::Common::JString appID = L"<ec02c427-5314-40b3-9328-d9d590465f14>";
//	static const ExitGames::Common::JString appVersion = L"1.0";
//	
//	SampleNetwork networkLogic(appID, appVersion);
//	networkLogic.connect();
//
//	//while (!shouldExit)
//	//{
//	//	networkLogic.run();
//	//	Sleep(100);
//	//}
//
//	networkLogic.disconnect();
//}

//ルームの名前とルームで許可されるプレイヤーの人数が設定される
//クライアントは自動的に新しいルームに入室する
//まだルームが存在していない場合には、参加者がいなくても作成される
//最後のプレイヤーが退室するまで、ルームは存在する
//void SampleNetwork::createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
//{
//	mLoadBalancingClient.opCreateRoom(roomName, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(maxPlayers));
//}