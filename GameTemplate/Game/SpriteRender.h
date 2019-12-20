#pragma once
#include "ShaderResourceView.h"

namespace Engine {
	namespace prefab {
		class SpriteRender
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

		private:
			bool m_isDraw3D = false;		//3D空間で描画する
			ShaderResourceView m_texture;		//テクスチャ
		};
	}
}