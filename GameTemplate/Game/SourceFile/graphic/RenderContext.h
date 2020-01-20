#pragma once
#include "ConstantBuffer.h"
#include "GPUBuffer/VertexBuffer.h"
#include "ShaderResourceView.h"
#include "GPUBuffer/IndexBuffer.h"
#include "graphics/Shader.h"

namespace Engine {

	class RenderContext
	{
	public:
		RenderContext() {}
		~RenderContext() {}

		/*
		������
		pD3DDeviceContextv D3D�f�o�C�X�R���e�L�X�g�B
		*/
		void Init(ID3D11DeviceContext*pD3DDeviceContext, ID3D11DeviceContext*pD3DDeferredDeviceContext);

		/*
		�T�u���\�[�X���X�V
		destRes		�R�s�[��
		srcRes		�R�s�[��
		*/
		template<class TBuffer, class SrcBuffer>
		void UpdateSubresource(TBuffer&gpuBuffer, const SrcBuffer*buffer)
		{
			if (gpuBuffer.GetBody() != nullptr)
			{
				m_pD3DDeviceContext->UpdateSubresource(gpuBuffer.GetBody(), 0, NULL, buffer, 0, 0);
			}
		}

		/*
		VS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�
		slotNo		�X���b�g�ԍ�
		cb		�萔�o�b�t�@
		*/
		void VSSetConstantBuffer(
			UINT slotNo,		//int�^�̃X���b�g�ԍ�
			ConstantBuffer&cb		//�萔�o�b�t�@
		)
		{
			m_pD3DDeviceContext->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*
		PS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�
		slotNo		�X���b�g�ԍ�
		cb		�萔�o�b�t�@
		*/
		void PSSetConstantBuffer(
			UINT slotNo,		//int�^�̃X���b�g�ԍ�
			ConstantBuffer& cb		//�萔�o�b�t�@
		)
		{
			m_pD3DDeviceContext->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*
		PS�X�e�[�W��SRV��ݒ�
		slotNo		�X���b�g�ԍ�
		srv		SRV
		*/
		void PSSetShaderResource(int slotNo, ShaderResourceView&srv)
		{
			m_pD3DDeviceContext->PSSetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/*
		�s�N�Z���V�F�[�_�[��ݒ�
		shader		���_�V�F�[�_�[
		*/
		void PSSetShader(Shader&shader)
		{
			m_pD3DDeviceContext->PSSetShader((ID3D11PixelShader*)shader.GetBody(), NULL, 0);
		}

		void RSSetState(ID3D11RasterizerState*prasterizerstate)
		{
			RasterizerState = prasterizerstate;
			m_pD3DDeviceContext->RSSetState(prasterizerstate);
		}
	private:
		//���̓��C�A�E�g��ݒ�
		void IASetInputLayout(ID3D11InputLayout*inputLayout)
		{
			m_pD3DDeviceContext->IASetInputLayout(inputLayout);
		}

	public:
		/*
		���_�V�F�[�_�[��ݒ�
		shader		���_�V�F�[�_�[
		*/
		void VSSetShader(Shader&shader)
		{
			IASetInputLayout(shader.GetInputLayout());
			m_pD3DDeviceContext->VSSetShader((ID3D11VertexShader*)shader.GetBody(), NULL, 0);
		}

		//���_�o�b�t�@��ݒ�
		void IASetVertexBuffer(VertexBuffer& vertexBuffer)
		{
			UINT offset = 0;
			UINT stride = vertexBuffer.GetStride();		//�X�g���C�h���擾
			m_pD3DDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.GetBody(), &stride, &offset);
		}

		//�C���f�b�N�X�o�b�t�@��ݒ�
		void IASetIndexBuffer(IndexBuffer& indexBuffer)
		{
			IndexBuffer::EnIndexType type = indexBuffer.GetIndexType();
			m_pD3DDeviceContext->IASetIndexBuffer(
				indexBuffer.GetBody(),
				type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
				0
			);
		}

		//�v���~�e�B�u�̃g�|���W�[��ݒ�
		//topology		�g�|���W�[
		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			m_pD3DDeviceContext->IASetPrimitiveTopology(topology);
		}

		/*
		�C���f�b�N�X�t���`��
		indexCount		�C���f�b�N�X�̐�
		StartIndexLocation		�`����J�n����C���f�b�N�X�̈ʒu�B���0�ő��v
		BaseVertexLocation		�x�[�X���_�C���f�b�N�X�B���0�ő��v
		*/
		void DrawIndexed(
			_In_ UINT IndexCount,		//�C���f�b�N�X�̐�
			_In_ UINT StartIndexLocation,		//�`����J�n����C���f�b�N�X�̈ʒu
			_In_ INT BaseVertexLocation)		//�x�[�X���_�C���f�b�N�X
		{
			m_pD3DDeviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
		}

		/*
		�`��
		vartexCount		���_��
		startVertexLocation		�`����J�n���钸�_�̈ʒu�B���0�ő��v
		*/
		void Draw(
			unsigned int vertexCount,		//���_��
			unsigned int startVertexLocation		//�`����J�n���钸�_�̈ʒu
		)
		{
			m_pD3DDeviceContext->Draw(vertexCount, startVertexLocation);
		}

	private:
		ID3D11DeviceContext* m_pD3DImmidiateDeviceContext = nullptr;
		ID3D11DeviceContext* m_pD3DDeviceContext = nullptr;		//�`��R�}���h��ς�ł����R���e�L�X�g�B
		ID3D11RasterizerState* RasterizerState = nullptr;		//�摜���r�b�g�}�b�v�ɂ���
	};
}