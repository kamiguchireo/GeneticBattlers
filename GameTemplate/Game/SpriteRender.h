#pragma once
#include "ShaderResourceView.h"
#include "SourceFile/graphic/2D/Sprite.h"

namespace Engine {
	namespace prefab {
		class SpriteRender:public IGameObject
		{
		public:
			//コンストラクタ
			SpriteRender() {}
			/*
			初期化
			texFilePath		テクスチャファイルパス
			w		幅
			h		高さ
			isDraw3D		3D空間で描写する
			*/
			void Init(const wchar_t*texFilePath, float w, float h, bool isDraw3D = false);

			//アップデート関数
			void Update();
			//セット関係
			void SetPosition(CVector3 pos)
			{
				m_position = pos;
			}
			void SetRotation(CQuaternion rot)
			{
				m_rotation = rot;
			}
			void SetScale(CVector3 scale)
			{
				m_scale = scale;
			}
			void SetPivot(CVector2 pivot)
			{
				m_pivot = pivot;
			}
			void SetMulColor(const CVector3& mulColor)
			{
				m_sprite.SetMulColor(mulColor);
			}
			//描画
			void PostRender(RenderContext&rc)override final;
		private:
			bool m_isDraw3D = false;		//3D空間で描画する
			ShaderResourceView m_texture;		//テクスチャ
			Sprite m_sprite;		//スプライト
			CVector3 m_position = { 0.0,0.0,5.0 };			//座標。
			CQuaternion m_rotation = CQuaternion::Identity();			//!<回転。
			CVector3 m_scale = CVector3::One();			//拡大率。
			CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット。
		};
	}
}