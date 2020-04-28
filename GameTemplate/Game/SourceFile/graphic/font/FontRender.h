#pragma once
#include "Font.h"

namespace Engine
{
	namespace prefab {
		//フォントレンダー
		class FontRender:public IGameObject
		{
		public:
			FontRender(){}
			~FontRender(){}

			//フォントを設定
			//デフォルトフォントから変更したい場合は
			//DirectX::SpriteFontを使用して、フォントをロードして差し替えてください
			//font		フォント
			void SetFont(DirectX::SpriteFont*font)
			{
				m_font.SetFont(font);
			}

			//テキストを設定
			//text		テキスト
			void SetText(const wchar_t*text)
			{
				//wcscmpは2つの文字列を比較する
				if (wcscmp(m_text.c_str(), text) != 0)
				{
					//文字列が変わった
					m_text = text;
				}
			}

			//フォントを表示する座標を設定
			//フォントの座標は
			//(0.0f,0.0f)で画面の中央です
			//右方向がX+
			//上方向がY+の座標系です
			void SetPosition(const CVector2&pos)
			{
				m_position = pos;
			}

			//フォントのカラーを設定
			//引数のxyzはrgbの値を指定
			//例）真っ赤にしたかったらxyzを(1.0f,0.0f,0.0f)と指定してください
			//color		色
			void SetColor(const CVector3&color)
			{
				m_color = color;
			}		
			void SetColor(const CVector4& color)
			{
				m_color = color;
			}

			//回転を設定
			//rotation		回転角度。単位はラジアン
			void SetRotation(float rotation)
			{
				m_rotation = rotation;
			}

			//拡大率を設定
			//scale		拡大率
			void SetScale(float scale)
			{
				m_scale = scale;
			}

			//ピボットを設定
			//フォントの基点を設定します
			//(0.5f,0.5f)で画像の中心が基点
			//(0.0f,0.0f)で画像の左下
			//(1.0f,1.0f)で画像の右上
			//pivot		基点
			void SetPivot(const CVector2&pivot)
			{
				m_pivot = pivot;
			}

			bool Start();
			void Update();
		private:
			Font m_font;		//フォント
			std::wstring m_text;		//テキスト。
			CVector2 m_position = CVector2::Zero();		//座標
			CVector4 m_color = CVector4::White();		//カラー
			float m_rotation = 0.0f;		//回転
			float m_scale = 1.0f;		//拡大率
			CVector2 m_pivot  = CVector2::Zero();		//ピボット
		};
	}
}