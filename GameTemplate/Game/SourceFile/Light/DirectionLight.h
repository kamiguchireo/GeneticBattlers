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

			//�A�N�e�B�u�t���O�̕ύX
			//�f�B���N�V�������C�g��L���ɂ��邩�ǂ���
			//�����Ȃ�1������
			//�����ݒ�ł�0�������Ă���̂ł��ׂẴ��f���Ń��C�g���L��
			void SetActiveDLFlag(int i)
			{
				m_dirLight.ActiveFlag[0] = i;
			}
			void Draw();

			//�萔�o�b�t�@�̏�����
			void InitConstantBuffer();

			//�����œn���ꂽ�����l��16�̔{���ɐ؂�グ
			int Raundup16(int n)
			{
				return (((n - 1) / 16) + 1) * 16;
			}
		private:
			struct SDirectionLight 
			{
				CVector4 direction = CVector4::White();		//���C�g�̌���
				CVector4 color = CVector4::White();		//���C�g�̐F
				int ActiveFlag[4];		//�A�N�e�B�u�t���O0�̎��ɗL���ɂ���
				float				specPow;			//���ʔ��˂̍i��
			};
			SDirectionLight m_dirLight;
			ID3D11Buffer* m_lightCb = nullptr;		//���C�g�p�̒萔�o�b�t�@
			D3D11_BUFFER_DESC bufferDesc;
		};
	}
}