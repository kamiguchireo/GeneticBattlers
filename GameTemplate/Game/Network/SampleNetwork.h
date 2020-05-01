#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/LoadBalancing-cpp/inc/client.h"
#include "Photon/Common-cpp/inc/Logger.h"
#include "Network/Listener.h"

class SampleNetwork
{
public:
	SampleNetwork(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
	~SampleNetwork();
	
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
		mLoadBalancingClient.opJoinRandomOrCreateRoom();
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

	void joina()
	{
		// join random rooms easily, filtering for specific room properties, if needed
		ExitGames::Common::Hashtable expectedCustomRoomProperties;

		// custom props can have any name but the key must be string
		expectedCustomRoomProperties.put(L"map", 1);

		// joining a random room with the map we selected before
		mLoadBalancingClient.opJoinRandomRoom(expectedCustomRoomProperties);
	}
	//イベントの送信
	void SendEvent()
	{
		nByte eventCode = 1; // use distinct event codes to distinguish between different types of events (for example 'move', 'shoot', etc.)
		ExitGames::Common::Hashtable evData; // organize your payload data in any way you like as long as it is supported by Photons serialization
		bool sendReliable = false; // send something reliable if it has to arrive everywhere
		mLoadBalancingClient.opRaiseEvent(sendReliable, evData, eventCode);
	}

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

	void boolExit(bool a)
	{
		shouldExit = a;
	}

	//シングルトンパターン。
	static SampleNetwork* GetInstance()
	{
		return m_instance;
	}
private:
	static SampleNetwork* m_instance;	//インスタンス。

	//ネットワークの接続をやめるかどうか
	//trueにしたらネットワークの処理はされません
	bool shouldExit = false;

	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	Listener mListener;
	ExitGames::Common::Logger mLogger;
	ExitGames::Common::Hashtable expectedCustomRoomProperties;
};

