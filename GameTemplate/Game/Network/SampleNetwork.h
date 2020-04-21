#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/LoadBalancing-cpp/inc/client.h"
#include "Photon/Common-cpp/inc/Logger.h"
#include "Network/Listener.h"

class SampleNetwork
{
public:
	SampleNetwork(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
	
	//ゲームへの接続
	void connect(void);

	//ゲームの切断
	//接続したら終わるときに必ず呼んでください
	void disconnect(void);
	
	//これを呼ばないとネットに接続できていても動作しません
	//1秒間に20～30回呼んでください
	void run(void);
	
	//新しいゲームルームの作成
	//roomName		部屋の名前
	//maxPlayers	入れる最大人数
	void createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
	{
		mLoadBalancingClient.opCreateRoom(roomName, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(maxPlayers));
	}

	//ゲームルームの検索
	//ランダムな部屋を検索して入る
	void JoinRoom()
	{
		expectedCustomRoomProperties;
	}
	//任意の部屋を検索して入る
	void JoinCostomRoom(const ExitGames::Common::JString& roomName)
	{
		expectedCustomRoomProperties.put(roomName, 1);
	}
	//以前参加したマップでランダムな部屋に入る
	void JoinBeforeRoom()
	{
		mLoadBalancingClient.opJoinRandomRoom(expectedCustomRoomProperties);
	}

	//イベントの送信
	void SendEvent(int evData)
	{
		nByte eventCode = 2;
		bool sendReliable = false;
		mLoadBalancingClient.opRaiseEvent(sendReliable, evData, eventCode);
	}
	//イベントの送信
	void SendEvent(float evData)
	{
		nByte eventCode = 3;
		bool sendReliable = false;
		float a = evData;
		mLoadBalancingClient.opRaiseEvent(sendReliable, a, eventCode);
	}

	//イベントの受信
	void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

private:
	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	Listener mListener;
	ExitGames::Common::Logger mLogger;
	ExitGames::Common::Hashtable expectedCustomRoomProperties;
};

