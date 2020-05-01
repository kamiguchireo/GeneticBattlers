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
		mLoadBalancingClient.opJoinRandomOrCreateRoom();
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

	void joina()
	{
		// join random rooms easily, filtering for specific room properties, if needed
		ExitGames::Common::Hashtable expectedCustomRoomProperties;

		// custom props can have any name but the key must be string
		expectedCustomRoomProperties.put(L"map", 1);

		// joining a random room with the map we selected before
		mLoadBalancingClient.opJoinRandomRoom(expectedCustomRoomProperties);
	}
	//�C�x���g�̑��M
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
	//�C�x���g�̑��M
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

	//�V���O���g���p�^�[���B
	static SampleNetwork* GetInstance()
	{
		return m_instance;
	}
private:
	static SampleNetwork* m_instance;	//�C���X�^���X�B

	//�l�b�g���[�N�̐ڑ�����߂邩�ǂ���
	//true�ɂ�����l�b�g���[�N�̏����͂���܂���
	bool shouldExit = false;

	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	Listener mListener;
	ExitGames::Common::Logger mLogger;
	ExitGames::Common::Hashtable expectedCustomRoomProperties;
};

