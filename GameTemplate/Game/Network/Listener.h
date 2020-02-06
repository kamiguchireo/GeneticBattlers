#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/Common-cpp/inc/JVector.h"
#include "Photon/Common-cpp/inc/Object.h"
#include "Photon/LoadBalancing-cpp/inc/listener.h"

class Listener:public ExitGames::LoadBalancing::Listener
{
public:
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string){}
	virtual void connectionErrorReturn(int errorCode) {}
	virtual void clientErrorReturn(int errorCode) {}
	virtual void warningReturn(int warningCode) {}
	virtual void serverErrorReturn(int errorCode) {}
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player) {}
	virtual void leaveRoomEventAction(int playerNr, bool isInactive) {}
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) {}
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster) {}
	virtual void disconnectReturn(void) {}
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString) {}

};