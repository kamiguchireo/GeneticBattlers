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
	//���[���ɒN�����Q��������joinRoomEventAction���Ă΂�܂�
	void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player) {}
	void leaveRoomEventAction(int playerNr, bool isInactive) {}
	//���[���ŃC�x���g�̑��M�������cunstomEventAction���Ă΂�܂�
	void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) 
	{
		//// logging the string representation of the eventContent can be really useful for debugging, but use with care: for big events this might get expensive
		//EGLOG(ExitGames::Common::DebugLevel::ALL, L"an event of type %d from player Nr %d with the following content has just arrived: %ls", eventCode, playerNr, eventContent.toString(true).cstr());

		switch (eventCode)
		{
		case 1:
		{
			// you can access the content as a copy (might be a bit expensive for really big data constructs)
			ExitGames::Common::Hashtable content = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent).getDataCopy();
			// or you access it by address (it will become invalid as soon as this function returns, so (any part of the) data that you need to continue having access to later on needs to be copied)
			ExitGames::Common::Hashtable* pContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent).getDataAddress();
		}
		break;
		case 2:
		{
			// of course the payload does not need to be a Hashtable - how about just sending around for example a plain 64bit integer?
			long long content = ExitGames::Common::ValueObject<long long>(eventContent).getDataCopy();
			//��������񂱂�ł�����H�H
			long long i = content;
		}
		break;
		case 3:
		{
			// or an array of floats?
			float Content = ExitGames::Common::ValueObject<float>(eventContent).getDataCopy();
			float* pContent = ExitGames::Common::ValueObject<float*>(eventContent).getDataCopy();
			float** ppContent = ExitGames::Common::ValueObject<float*>(eventContent).getDataAddress();
			short contentElementCount = *ExitGames::Common::ValueObject<float*>(eventContent).getSizes();
			//��������񂱂�ł�����H�H
			float f = Content;
			// when calling getDataCopy() on Objects that hold an array as payload, then you must deallocate the copy of the array yourself using deallocateArray()!
			ExitGames::Common::MemoryManagement::deallocateArray(pContent);
		}
		break;
		default:
		{
			// have a look at demo_typeSupport inside the C++ client SDKs for example code on how to send and receive more fancy data types
		}
		break;
		}
	}
	void disconnectReturn(void) {}
	void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString) {}
	
	void connectReturn(int errorCode,
		const ExitGames::Common::JString& errorString,
		const ExitGames::Common::JString& region,
		const ExitGames::Common::JString& cluster)
	{
		//�G���[��e��
		//errorCode��0�ȊO�Ȃ�G���[������
		if (errorCode) 
		{
			//�����ɓ���ΐڑ��ł��Ă��܂���
			return;
		}
		
		//�����ɓ���ΐڑ��ł��Ă��܂�

	}

};