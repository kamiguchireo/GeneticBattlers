#pragma once

namespace Engine {
	namespace prefab{
		class DirectionLight :public IGameObject
		{
		public:
			DirectionLight();
			~DirectionLight();

			//�萔�o�b�t�@�̏�����
			void InitConstantBuffer();
		private:
			struct SDirectionLight 
			{
				CVector4 direction = CVector4::White();		//���C�g�̌���
				CVector4 color = CVector4::White();		//���C�g�̐F
			};
			ID3D11Buffer* m_lightCb = nullptr;		//���C�g�p�̒萔�o�b�t�@
			D3D11_BUFFER_DESC bufferDesc;
		};
	}
}