#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/Common-cpp/inc/JVector.h"
#include "Photon/Common-cpp/inc/Object.h"
#include "Photon/LoadBalancing-cpp/inc/listener.h"

class Listener:public ExitGames::LoadBalancing::Listener
{
public:
	void debugReturn(int debugLevel, const ExitGames::Common::JString& string){}
	void connectionErrorReturn(int errorCode) {}
	void clientErrorReturn(int errorCode) {}
	void warningReturn(int warningCode) {}
	void serverErrorReturn(int errorCode) {}
	void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player) {}
	void leaveRoomEventAction(int playerNr, bool isInactive) {}
	void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) {}
	void disconnectReturn(void) {}
	void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString) {}
	
	void connectReturn(int errorCode,
		const ExitGames::Common::JString& errorString,
		const ExitGames::Common::JString& region,
		const ExitGames::Common::JString& cluster)
	{
		//ÉGÉâÅ[ÇíeÇ≠
		if (errorCode) { std::cout << "connect error\n"; return; }
		std::cout << "connected\n";
	}

};