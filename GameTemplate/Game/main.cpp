#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
#include "SourceFile/Sound/SoundEngine.h"
#include "SourceFile/Light/DirectionLight.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	g_camera2D.SetPosition({ 0.0f, 0.0f, 0.0f });
	g_camera2D.SetTarget({ 0.0f, 0.0f, 10.0f });
	g_camera2D.SetFar(100.0f);
	
	//Game�̐����B
	//�G���W���̎������Ă�̂Œ��g�͐G��Ȃ���
	//NewGO<Game>(0, nullptr);

	//�����ɕK�v�Ȃ��̂�NewGO���Ă����Ă�������
	NewGO<TitleScene>(0, nullptr);
	NewGO<Fade>(1, "Fade");
	
	//�G�t�F�N�T�[�}�l�[�W���[�̏�����
	//�R�����g�A�E�g���Ȃ���
	g_graphicsEngine->managerInit();

	//�T�E���h�֌W�̏�����
	//�R�����g�A�E�g���Ȃ���
	CSoundEngine se;
	se.Init();

	g_camera2D.Update2D();
	
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();

		GameObjectManager().Start();
		GameObjectManager().Update();
		//�J�����̍X�V�B
		g_camera3D.Update();


		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}