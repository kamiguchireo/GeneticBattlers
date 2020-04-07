#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/LoadBalancing-cpp/inc/client.h"
#include "Photon/Common-cpp/inc/Logger.h"
#include "Network/Listener.h"

class SampleNetwork
{
public:
	SampleNetwork(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
	void connect(void);
	void disconnect(void);
	void run(void);
	void createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
	{
		mLoadBalancingClient.opCreateRoom(roomName, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(maxPlayers));
	}
private:
	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	Listener mListener;
	ExitGames::Common::Logger mLogger;

};

