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

private:
	ExitGames::LoadBalancing::Client m_LoadBalancingClient;
	Listener m_Listener;
	ExitGames::Common::Logger mLogger;
};
