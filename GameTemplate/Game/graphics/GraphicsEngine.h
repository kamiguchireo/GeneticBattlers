#pragma once
#include "Camera.h"
#include "SourceFile/graphic/RenderContext.h"

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
		return m_2DCamera;
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
private:
	Camera m_mainCamera;		//�J����
	Camera m_2DCamera;
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
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��