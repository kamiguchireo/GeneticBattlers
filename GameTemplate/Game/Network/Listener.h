#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/Common-cpp/inc/JVector.h"
#include "Photon/Common-cpp/inc/Object.h"
#include "Photon/LoadBalancing-cpp/inc/listener.h"
#include "../gameScenes/NetScenes/NetScenes.h"

class Listener:public ExitGames::LoadBalancing::Listener
{
public:
	void debugReturn(int debugLevel, const ExitGames::Common::JString& string){}
	void connectionErrorReturn(int errorCode) {}
	void clientErrorReturn(int errorCode) {}
	void warningReturn(int warningCode) {}
	void serverErrorReturn(int errorCode) {}
	//ルームに誰かが参加したらjoinRoomEventActionが呼ばれます
	void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
	{
		if (playernrs.getSize() == 2)
		{
			NetScenes::GetInstance()->SetStateSend();
		}
	}
	void leaveRoomEventAction(int playerNr, bool isInactive) {}
	//ルームでイベントの送信があればcunstomEventActionが呼ばれます
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
			int content = ExitGames::Common::ValueObject<int>(eventContent).getDataCopy();
			//↑でcontentに値が入ってます
			//NetScenes::GetInstance()->PushBackData(content);
		}
		break;
		case 3:
		{
			// or an array of floats?
			float Content = ExitGames::Common::ValueObject<float>(eventContent).getDataCopy();
			//↑でContentに値が入ってます
			float* pContent = ExitGames::Common::ValueObject<float*>(eventContent).getDataCopy();
			float** ppContent = ExitGames::Common::ValueObject<float*>(eventContent).getDataAddress();
			short contentElementCount = *ExitGames::Common::ValueObject<float*>(eventContent).getSizes();
			// when calling getDataCopy() on Objects that hold an array as payload, then you must deallocate the copy of the array yourself using deallocateArray()!
			ExitGames::Common::MemoryManagement::deallocateArray(pContent);
			//NetScenes::GetInstance()->PushBackData(Content);
		}
		break;
		case 4:
		{
			//HashTableが送られてきます
			//HashTableは列挙型みたいなやつです
			//指定したキーを入れると値が取得できます
			//HashTableをコピー
			ExitGames::Common::Hashtable hashData = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent).getDataCopy();
			//int i;
			//float f;
			//HashTableに列挙型がまるまる入っていると考えてください
			//↓のようにして値を取り出せます
			//if (hashData.getValue((nByte)1))
			//{
			//	i = (ExitGames::Common::ValueObject<int>(hashData.getValue((nByte)1))).getDataCopy();
			//}
			//if (hashData.getValue((nByte)2))
			//{
			//	f = (ExitGames::Common::ValueObject<float>(hashData.getValue((nByte)2))).getDataCopy();
			//}
			//ExitGames::Common::Hashtable hash = ExitGames::Common::ValueObject <ExitGames::Common::Hashtable>(eventContent).getDataCopy();
			//auto i = (ExitGames::Common::ValueObject<nByte>(hash.getValue((nByte)1))).getDataCopy();
			//float f = (ExitGames::Common::ValueObject<nByte>(hash.getValue((nByte)2))).getDataCopy();

			int list = (ExitGames::Common::ValueObject<int>(hashData.getValue((nByte)1))).getDataCopy();
			int skill = (ExitGames::Common::ValueObject<int>(hashData.getValue((nByte)2))).getDataCopy();
			int target = (ExitGames::Common::ValueObject<int>(hashData.getValue((nByte)3))).getDataCopy();
			float rate = (ExitGames::Common::ValueObject<float>(hashData.getValue((nByte)4))).getDataCopy();
			NetScenes::GetInstance()->PushBackData(list,skill,target,rate);
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
		//エラーを弾く
		//errorCodeが0以外ならエラーがある
		if (errorCode) 
		{
			//ここに入れば接続できていません
			return;
		}
		
		//ここに入れば接続できています

	}

};