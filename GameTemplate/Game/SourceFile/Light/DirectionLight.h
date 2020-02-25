#pragma once
#include "SourceFile/GameObject/GameObjectManager.h"
namespace Engine {
	namespace prefab{
		class DirectionLight :public IGameObject
		{
		public:
			DirectionLight();
			~DirectionLight();

			//bool Start();
			//void Update();

			//ディレクションライトの向き
			void SetDirection(CQuaternion dir)
			{
				dir.Multiply(m_dirLight.direction);

				//m_dirLight.direction = dir;
			}

			//ディレクションライトの色
			void SetColor(CVector4 color)
			{
				m_dirLight.color = color;
			}


			void Draw();

			//定数バッファの初期化
			void InitConstantBuffer();
		private:
			struct SDirectionLight 
			{
				CVector4 direction = CVector4::White();		//ライトの向き
				CVector4 color = CVector4::White();		//ライトの色
			};
			SDirectionLight m_dirLight;
			ID3D11Buffer* m_lightCb = nullptr;		//ライト用の定数バッファ
			D3D11_BUFFER_DESC bufferDesc;
		};
	}
}