#pragma once

namespace Engine {
	class RenderTarget
	{
	public:
		RenderTarget();
		~RenderTarget();

		//�������
		void Release();

		//�����_�����O�^�[�Q�b�g�̍쐬
		//w �e�N�X�`���̕�
		//h �e�N�X�`���̍���
		void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);

		//�����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���̃N���A
		//clearColor	�N���A�J���[
		void ClearRenderTarget(float*clearColor);

		//�����_�����O�^�[�Q�b�g�r���[���擾
		ID3D11RenderTargetView*GetRenderTargetView()
		{
			return m_renderTargetView;
		}

		//�f�v�X�X�e���V���r���[���擾
		ID3D11DepthStencilView*GetDepthStensilView()
		{
			return m_depthStencilView;
		}

		//�����_�����O�^�[�Q�b�g��SRV���擾
		ID3D11ShaderResourceView*GetRenderTargetSRV()
		{
			return m_renderTargetSRV;
		}

		//�r���[�|�[�g�̎擾
		D3D11_VIEWPORT*GetViewport()
		{
			return &m_viewport;
		}

		//SRV�̎擾
		ID3D11ShaderResourceView* GetSRV()
		{
			return m_renderTargetSRV;
		}
	private:
		ID3D11Texture2D* m_renderTargetTex = nullptr;		//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
		//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬
		D3D11_TEXTURE2D_DESC texDesc = { 0 };
		ID3D11RenderTargetView*	m_renderTargetView = nullptr;		//�����_�[�^�[�Q�b�g�r���[�B
		//�f�v�X�X�e���V���e�N�X�`���̍쐬
		D3D11_TEXTURE2D_DESC depthTexDesc;
		ID3D11Texture2D* m_depthStencilTex = nullptr;		//�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
		ID3D11DepthStencilView*	m_depthStencilView = nullptr;		//�f�v�X�X�e���V���r���[�B
		ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//�����_�����O�^�[�Q�b�g��SRV
		D3D11_VIEWPORT m_viewport;
	};

}