#pragma once
#include "Photon/Common-cpp/inc/JString.h"
#include "Photon/LoadBalancing-cpp/inc/client.h"
#include "Photon/Common-cpp/inc/Logger.h"
#include "Network/Listener.h"

class SampleNetwork
{
public:
	SampleNetwork(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
	
	//�Q�[���ւ̐ڑ�
	void connect(void);

	//�Q�[���̐ؒf
	//�ڑ�������I���Ƃ��ɕK���Ă�ł�������
	void disconnect(void);
	
	//������Ă΂Ȃ��ƃl�b�g�ɐڑ��ł��Ă��Ă����삵�܂���
	//1�b�Ԃ�20�`30��Ă�ł�������
	void run(void);
	
	//�V�����Q�[�����[���̍쐬
	//roomName		�����̖��O
	//maxPlayers	�����ő�l��
	void createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
	{
		mLoadBalancingClient.opCreateRoom(roomName, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(maxPlayers));
	}

	//�Q�[�����[���̌���
	//�����_���ȕ������������ē���
	void JoinRoom()
	{
		expectedCustomRoomProperties;
	}
	//�C�ӂ̕������������ē���
	void JoinCostomRoom(const ExitGames::Common::JString& roomName)
	{
		expectedCustomRoomProperties.put(roomName, 1);
	}
	//�ȑO�Q�������}�b�v�Ń����_���ȕ����ɓ���
	void JoinBeforeRoom()
	{
		mLoadBalancingClient.opJoinRandomRoom(expectedCustomRoomProperties);
	}

	//�C�x���g�̑��M
	void SendEvent(int evData)
	{
		nByte eventCode = 2;
		bool sendReliable = false;
		mLoadBalancingClient.opRaiseEvent(sendReliable, evData, eventCode);
	}
	//�C�x���g�̑��M
	void SendEvent(float evData)
	{
		nByte eventCode = 3;
		bool sendReliable = false;
		float a = evData;
		mLoadBalancingClient.opRaiseEvent(sendReliable, a, eventCode);
	}

	//�C�x���g�̎�M
	void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

private:
	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	Listener mListener;
	ExitGames::Common::Logger mLogger;
	ExitGames::Common::Hashtable expectedCustomRoomProperties;
};

