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
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"�ڑ��ł��܂���ł��������I�I");

	}
}

//1�b��10�`20��ǂ�ł�������
void SampleNetwork::run(void)
{
	//������Ă΂Ȃ�����A�l�b�g���[�N�͑S����������܂���
	mLoadBalancingClient.service();
}

//�A�v���P�[�V�������I������Ƃ���
//���[�U�[�����O�A�E�g����Ƃ��ɕK���Ă�ł�������
void SampleNetwork::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

//void main(void)
//{
//	//�����ɍ����app id���Z�b�g����
//	static const ExitGames::Common::JString appID = L"<ec02c427-5314-40b3-9328-d9d590465f14>";
//	static const ExitGames::Common::JString appVersion = L"1.0";
//	
//	SampleNetwork networkLogic(appID, appVersion);
//	networkLogic.connect();
//
//	//while (!shouldExit)
//	//{
//	//	networkLogic.run();
//	//	Sleep(100);
//	//}
//
//	networkLogic.disconnect();
//}

//���[���̖��O�ƃ��[���ŋ������v���C���[�̐l�����ݒ肳���
//�N���C�A���g�͎����I�ɐV�������[���ɓ�������
//�܂����[�������݂��Ă��Ȃ��ꍇ�ɂ́A�Q���҂����Ȃ��Ă��쐬�����
//�Ō�̃v���C���[���ގ�����܂ŁA���[���͑��݂���
//void SampleNetwork::createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
//{
//	mLoadBalancingClient.opCreateRoom(roomName, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(maxPlayers));
//}