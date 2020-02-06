#pragma once
#include "EffekseerRuntime130/src/Effekseer/Effekseer.h"

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
			void SetSacle(const CVector3&scale)
			{
				m_scale = scale;
			}

			//更新
			//void Update();
		private:
			Effekseer::Effect*m_effect = nullptr;
			Effekseer::Handle m_handle = -1;
			CVector3 m_position = CVector3::Zero();		//座標
			CQuaternion m_rotation = CQuaternion::Identity();		//回転
			CVector3 m_scale = CVector3::One();		//拡大
		};
	}
}


