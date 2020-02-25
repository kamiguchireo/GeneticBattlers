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

			//�f�B���N�V�������C�g�̌���
			void SetDirection(CQuaternion dir)
			{
				dir.Multiply(m_dirLight.direction);

				//m_dirLight.direction = dir;
			}

			//�f�B���N�V�������C�g�̐F
			void SetColor(CVector4 color)
			{
				m_dirLight.color = color;
			}


			void Draw();

			//�萔�o�b�t�@�̏�����
			void InitConstantBuffer();
		private:
			struct SDirectionLight 
			{
				CVector4 direction = CVector4::White();		//���C�g�̌���
				CVector4 color = CVector4::White();		//���C�g�̐F
			};
			SDirectionLight m_dirLight;
			ID3D11Buffer* m_lightCb = nullptr;		//���C�g�p�̒萔�o�b�t�@
			D3D11_BUFFER_DESC bufferDesc;
		};
	}
}