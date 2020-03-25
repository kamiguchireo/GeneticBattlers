#pragma once
#include "Camera.h"
#include "SourceFile/graphic/RenderContext.h"
#include "SourceFile/graphic/2D/Sprite.h"
#include "EffekseerRendererDX11.h"
#include "Effekseer.h"
#include "SourceFile/graphic/ShadowMap.h"
//#include "SourceFile/graphic/RenderTarget.h"

enum EnRenderMode
{
	enRenderMode_CreateShadowMap,		//�V���h�E�}�b�v����
	enRenderMode_Normal,				//�ʏ탌���_�����O
	enRenderMode_silhouette,			//�V���G�b�g�����p�����_�����O
	enRenderMode_shadowReciever,		//�V���h�E���V�[�o�[�Ƃ��Đ���
};
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	Camera&GetMainCamera()
	{
		return m_mainCamera;		//�J����
	}
	Camera&Get2DCamera()
	{
		return g_camera2D;
	}

	void Execute2DDraw()
	{
		m_sprite.Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}
	//�����_�����O�R���e�L�X�g�̃C���X�^���X���擾
	Engine::RenderContext& GetRenderContext()
	{
		return m_renderContext;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();


	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}

	void managerInit();
	
	//Effekseer�}�l�[�W���̎擾�B 
	Effekseer::Manager& GetEffekseerManager()
	{
		return *m_manager;
	}

	EffekseerRenderer::Renderer& GetEffekseerRender()
	{
		return *m_renderer;
	}
	Effekseer::Effect* GraphicsEngine::CreateEffekseerEffect(const wchar_t* filePath)
	{
		return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
	}

	Engine::ShadowMap* GetShadowMap()
	{
		return &m_shadowmap;
	}
	ID3D11BlendState* GetBlendState()
	{
		return m_translucentBlendState;
	}

	void RtSpInit();
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, Engine::RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

	Engine::RenderTarget*GetRT()
	{
		return &m_mainRenderTarget;
	}

	Engine::Sprite*GetSp()
	{
		return &m_copyMainRtToFrameBufferSprite;
	}
	void InitRender();
private:
	Camera m_mainCamera;		//�J����
	//Camera m_2DCamera;
	Engine::Sprite m_sprite;
	Engine::RenderContext m_renderContext;		//�����_�����O�R���e�L�X�g�B
	//ID3D11DeviceContext* m_pImmediateContext = nullptr;		//D3D11�����f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_pDeferredDeviceContext = nullptr;		//D3D11�f�B�t�@�[�h�f�o�C�X�R���e�L�X�g
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	D3D11_FEATURE_DATA_THREADING m_featureDataThreading;
	Effekseer::Manager* m_manager = nullptr;
	EffekseerRenderer::Renderer* m_renderer = nullptr;
	Engine::ShadowMap m_shadowmap;
	ID3D11BlendState*m_translucentBlendState = nullptr;
	Engine::RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	Engine:: Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	CVector3 m_sposition = { 0.0,0.0,5.0 };			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
	CVector3 m_scale = CVector3::One();			//�g�嗦�B
	CVector2 m_pivot = Engine:: Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��