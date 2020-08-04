#pragma once
#include "SourceFile/Sound/SoundEngine.h"
#include "SourceFile/graphic/PostEffect.h"
//photon
#include "Photon/Common-cpp/inc/JString.h"
#include "Network/SampleNetwork.h"

namespace Engine {
	class EngineProcessing :public Noncopyable
	{
	public:
		EngineProcessing()
		{

		}

		~EngineProcessing()
		{

		}

		//�G���W���֌W�̏�����
		void Init();
		//�G���W���֌W�̃A�b�v�f�[�g
		void Update();

		void EffectDraw();
		//�|�X�g�G�t�F�N�g�̕`��
		void PostEffectDraw();

		//�����_�����O�^�[�Q�b�g��ύX����
		void ChangeRT();
		//�����_�����O�^�[�Q�b�g��߂�
		void ReturnRT();
		//���݂̃����_�����O�^�[�Q�b�g���N���A����
		void ClearRT();

		//�ŏI�I�ɉ�ʂɏo���X�v���C�g�̕`��
		void MainSpriteDraw();

	private:
		CSoundEngine se;		//�T�E���h�G���W��
		PostEffect m_postEffect;		//�|�X�g�G�t�F�N�g
		ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
		ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
		D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
		struct MainSpriteConfig
		{
			CVector3 m_sposition = { 0.0,0.0,5.0 };			//���W�B
			CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
			CVector3 m_scale = CVector3::One();			//�g�嗦�B
			CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
		};
		MainSpriteConfig MSC;
	};
}