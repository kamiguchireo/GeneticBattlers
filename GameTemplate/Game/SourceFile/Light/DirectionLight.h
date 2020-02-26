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
				//dir.Multiply(m_dirLight.direction);

				m_dirLight.direction = dir;
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

			//���ʔ��˂̃t���O
			//0�Ȃ�L��
			void SetActiveRLFlag(int i)
			{
				m_dirLight.ActiveFlag[1] = i;
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
				CQuaternion direction = { 1.0f,0.0f,0.0f,0.0f };	//���C�g�̌���
				CVector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };		//���C�g�̐F
				CVector3 eyePos;		//���_�̍��W
				float specPow;			//���ʔ��˂̍i��
				unsigned int ActiveFlag[3];		//�A�N�e�B�u�t���O0�̎��ɗL���ɂ���	
			};
			SDirectionLight m_dirLight;
			ID3D11Buffer* m_lightCb = nullptr;		//���C�g�p�̒萔�o�b�t�@
			D3D11_BUFFER_DESC bufferDesc;
		};
	}
}