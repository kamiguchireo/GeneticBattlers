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
			//描画
			void PostRender(RenderContext&rc)override final;
		private:
			bool m_isDraw3D = false;		//3D空間で描画する
			ShaderResourceView m_texture;		//テクスチャ
			Sprite m_sprite;		//スプライト
			CVector3 m_position = CVector3::Zero();			//座標。
			CQuaternion m_rotation = CQuaternion::Identity();			//!<回転。
			CVector3 m_scale = CVector3::One();			//拡大率。
			CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット。
		};
	}
}