#pragma once
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

namespace Engine {
	namespace prefab{
		class CEffect:public IGameObject
		{
		public:
			CEffect();
			~CEffect();

			//解放処理
			void Release();

			//エフェクトを再生
			//filePath		再生するエフェクトのファイルパス
			void Play(const wchar_t*filePath);

			//座標を設定
			void SetPosition(const CVector3& pos)
			{
				m_position = pos;
			}

			//回転の設定
			void SetRotation(const CQuaternion&rot)
			{
				m_rotation = rot;
			}

			//拡大率を設定
			void SetScale(const CVector3&scale)
			{
				m_scale = scale;
			}

			Effekseer::Effect*GetResource(int nameKey)
			{
				auto it = m_resourceMap.find(nameKey);
				if (it != m_resourceMap.end())
				{
					return it->second;
				}
				return nullptr;
			}

			void RegistResource(int nameKey,Effekseer::Effect*res)
			{
				m_resourceMap.insert(std::pair<int, Effekseer::Effect*>(nameKey, res));
			}

			//エフェクトが再生中か判定
			bool IsPlay()
			{
				return g_graphicsEngine->GetEffekseerManager().GetShown(m_handle);
			}

			//void managerInit();

			//Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath)
			//{
			//	return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
			//}

			//更新
			void Update();
			//void PostRender() override;
		private:
			std::map<int, Effekseer::Effect*> m_resourceMap;
			Effekseer::Effect*m_effect = nullptr;
			Effekseer::Handle m_handle = -1;
			//Effekseer::Manager* m_manager = nullptr;
			//EffekseerRenderer::Renderer* m_renderer = nullptr;
			CVector3 m_position = CVector3::Zero();		//座標
			CQuaternion m_rotation = CQuaternion::Identity();		//回転
			CVector3 m_scale = CVector3::One();		//拡大
		};
	}
}


