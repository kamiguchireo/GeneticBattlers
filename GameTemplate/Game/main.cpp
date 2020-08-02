#include "stdafx.h"
#include "system/system.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
#include "SourceFile/Engine.h"
//photon
#include "Photon/Common-cpp/inc/JString.h"
#include "Network/SampleNetwork.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//photon
	//�����ɍ����app id���Z�b�g����
	static const ExitGames::Common::JString appID = L"ec02c427-5314-40b3-9328-d9d590465f14";
	static const ExitGames::Common::JString appVersion = L"1.0";
	//�l�b�g���[�N�ɐڑ�
	SampleNetwork networkLogic(appID, appVersion);
	networkLogic.connect();
	
	EngineProcessing EP;		//�G���W���̏����֌W���܂Ƃ߂��N���X
	EP.Init();

	//Game�̐����B
	//�G���W���̎������Ă�̂Œ��g�͐G��Ȃ���
	//NewGO<Game>(0, nullptr);

	//�����ɕK�v�Ȃ��̂�NewGO���Ă����Ă�������	
	NewGO<TitleScene>(0, nullptr);
	NewGO<Fade>(3, "Fade");

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{	
		//�l�b�g���[�N�̍X�V
		networkLogic.run();
		
		//�J�����̍X�V�B
		g_camera3D.Update();

		//�`��J�n�B
		g_graphicsEngine->BegineRender();

		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//�����G���W���̍X�V�B
		g_physics.Update();

		//�G���W�����������̍X�V����
		EP.Update();

		////////////////////////////////////////////
		/////��������I�t�X�N���[�������_�����O/////
		////////////////////////////////////////////

		EP.ChangeRT();		//�����_�����O�^�[�Q�b�g��߂�

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�S�̂̍X�V�֐�
		GameObjectManager().Thread();

		EP.PostEffectDraw();		//�|�X�g�G�t�F�N�g��Draw

		EP.ReturnRT();		//�����_�����O�^�[�Q�b�g��߂�

		////////////////////////////////////////////
		///////�I�t�X�N���[�������_�����O�I��///////
		////////////////////////////////////////////

		EP.MainSpriteDraw();		//�ŏI�I�ɉ�ʑS�̂��X�v���C�g���������̂�`��
		
		//�`��I���B
		g_graphicsEngine->EndRender();
	}

	//�Q�[�����[�v�I�����Ƀl�b�g���[�N����ؒf����
	networkLogic.disconnect();
}