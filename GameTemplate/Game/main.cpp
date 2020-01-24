#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "SpriteRender.h"
#include "ShaderResourceView.h"
#include "SourceFile/graphic/2D/Sprite.h"

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
	//CGameObjectManager gameObject;

	//�Q�[���N���X�̐����B
	NewGO<Game>(0, nullptr);

	//�X�v���C�g�̊m�F�̂��߂̃|�C���^
	prefab::SpriteRender*m_spriteRender;

	//�X�v���C�g��������
	m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);
	const float FRAME_BUFFER_W = 1280.0;				//�t���[���o�b�t�@�̕��B
	const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B

	//ShaderResourceView m_srv;
	//Sprite sprite;
	//m_srv.CreateFromDDSTextureFromFile(L"Assets/sprite/win.dds");
	//sprite.Init(m_srv.GetBody(), 500.0f, 500.0f);
	//sprite.Update({0.0,0.0,5.0}, CQuaternion::Identity(), CVector3::One());
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
		//sprite.Update({ 0.0,0.0,5.0 }, CQuaternion::Identity(), CVector3::One());
		//sprite.Draw
		//(
		//	g_camera2D.GetViewMatrix(),
		//	g_camera2D.GetProjectionMatrix()
		//);
		//g_graphicsEngine->Execute2DDraw();

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}