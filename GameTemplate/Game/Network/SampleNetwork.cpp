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

void SampleNetwork::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	// logging the string representation of the eventContent can be really useful for debugging, but use with care: for big events this might get expensive
	EGLOG(ExitGames::Common::DebugLevel::ALL, L"an event of type %d from player Nr %d with the following content has just arrived: %ls", eventCode, playerNr, eventContent.toString(true).cstr());

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
	}
	break;
	case 3:
	{
		// or an array of floats?
		float* pContent = ExitGames::Common::ValueObject<float*>(eventContent).getDataCopy();
		float** ppContent = ExitGames::Common::ValueObject<float*>(eventContent).getDataAddress();
		short contentElementCount = *ExitGames::Common::ValueObject<float*>(eventContent).getSizes();
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