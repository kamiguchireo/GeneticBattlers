#pragma once

namespace Engine {
	namespace prefab{
		class DirectionLight :public IGameObject
		{
		public:
			DirectionLight();
			~DirectionLight();

			//定数バッファの初期化
			void InitConstantBuffer();
		private:
			struct SDirectionLight 
			{
				CVector4 direction = CVector4::White();		//ライトの向き
				CVector4 color = CVector4::White();		//ライトの色
			};
			ID3D11Buffer* m_lightCb = nullptr;		//ライト用の定数バッファ
			D3D11_BUFFER_DESC bufferDesc;
		};
	}
}