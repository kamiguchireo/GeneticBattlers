#include "stdafx.h"
#include "CEffect.h"

namespace Engine {
	namespace prefab {
		CEffect::CEffect()
		{
		}
		CEffect::~CEffect()
		{
			Release();
		}

		//解放処理
		void CEffect::Release()
		{
			if (m_handle != -1)
			{
				g_graphicsEngine->GetEffekseerManager().StopEffect(m_handle);
				m_handle = -1;
			}
		}

		//void CEffect::managerInit()
		//{
		//	//レンダラーを初期化
		//	m_renderer = EffekseerRendererDX11::Renderer::Create(
		//		g_graphicsEngine->GetD3DDevice(),
		//		g_graphicsEngine->GetD3DDeviceContext(),
		//		2000);

		//	//エフェクトマネージャーを初期化
		//	m_manager = Effekseer::Manager::Create(10000);
		//	//描画用インスタンスから描画機能を設定
		//	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		//	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		//	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		//	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		//	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		//	//描画用インスタンスからテクスチャの読み込み機能を設定
		//	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		//	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		//}

		void CEffect::Play(const wchar_t* filePath)
		{
			//managerInit();
			int nameKey = Util::MakeHash(filePath);
			m_effect = GetResource(nameKey);
			if (m_effect == nullptr)
			{
				//未登録
				m_effect = g_graphicsEngine->CreateEffekseerEffect(filePath);
				if (m_effect == nullptr)
				{
					//エフェクトのロードに失敗したぜ！
					//例外スローだ！やったね！ｗｗｗ
					throw;
				}
				RegistResource(nameKey,m_effect);
			}
			m_handle = g_graphicsEngine->GetEffekseerManager().Play(m_effect, 0, 0, 0);
		}

		void CEffect::Update()
		{
			//Effekseer::Matrix44 efCameraMat;
			//g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
			//Effekseer::Matrix44 efProjMat;
			//g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
			////カメラ行列とプロジェクション行列を設定。
			//g_graphicsEngine->GetEffekseerRender().SetCameraMatrix(efCameraMat);
			//g_graphicsEngine->GetEffekseerRender().SetProjectionMatrix(efProjMat);

			//g_graphicsEngine->GetEffekseerManager().Update();

			CMatrix m_Trans, m_Rot, m_Scale, m_Base = CMatrix::Identity();
			m_Trans.MakeTranslation(m_position);
			m_Rot.MakeRotationFromQuaternion(m_rotation);
			m_Scale.MakeScaling(m_scale);
			m_Base.Mul(m_Scale, m_Rot);
			m_Base.Mul(m_Base, m_Trans);
			g_graphicsEngine->GetEffekseerManager().SetBaseMatrix(m_handle, m_Base);

			//g_graphicsEngine->GetEffekseerRender().BeginRendering();
			//g_graphicsEngine->GetEffekseerManager().Draw();
			//g_graphicsEngine->GetEffekseerRender().EndRendering();

			if (IsPlay() == false)
			{
				//再生完了したら終わる
				DeleteGO(this);
			}
		}
		void CEffect::PostRender()
		{
			//取り合えずPostRenderに置くことでエフェクトを再生できるようにした。
			//tkEngineとは違うから直したかったらそっち参照。
			Effekseer::Matrix44 efCameraMat;
			g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
			Effekseer::Matrix44 efProjMat;
			g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
			//カメラ行列とプロジェクション行列を設定。
			g_graphicsEngine->GetEffekseerRender().SetCameraMatrix(efCameraMat);
			g_graphicsEngine->GetEffekseerRender().SetProjectionMatrix(efProjMat);

			//g_graphicsEngine->GetEffekseerManager().Update(g_gameTime.GetFrameDeltaTime() * 60.0f);

			g_graphicsEngine->GetEffekseerRender().BeginRendering();
			g_graphicsEngine->GetEffekseerManager().Draw();
			g_graphicsEngine->GetEffekseerRender().EndRendering();
		}
	}
}