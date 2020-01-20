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
		初期化
		pD3DDeviceContextv D3Dデバイスコンテキスト。
		*/
		void Init(ID3D11DeviceContext*pD3DDeviceContext, ID3D11DeviceContext*pD3DDeferredDeviceContext);

		/*
		サブリソースを更新
		destRes		コピー先
		srcRes		コピー元
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
		VSステージに定数バッファを設定
		slotNo		スロット番号
		cb		定数バッファ
		*/
		void VSSetConstantBuffer(
			UINT slotNo,		//int型のスロット番号
			ConstantBuffer&cb		//定数バッファ
		)
		{
			m_pD3DDeviceContext->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*
		PSステージに定数バッファを設定
		slotNo		スロット番号
		cb		定数バッファ
		*/
		void PSSetConstantBuffer(
			UINT slotNo,		//int型のスロット番号
			ConstantBuffer& cb		//定数バッファ
		)
		{
			m_pD3DDeviceContext->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*
		PSステージにSRVを設定
		slotNo		スロット番号
		srv		SRV
		*/
		void PSSetShaderResource(int slotNo, ShaderResourceView&srv)
		{
			m_pD3DDeviceContext->PSSetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/*
		ピクセルシェーダーを設定
		shader		頂点シェーダー
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
		//入力レイアウトを設定
		void IASetInputLayout(ID3D11InputLayout*inputLayout)
		{
			m_pD3DDeviceContext->IASetInputLayout(inputLayout);
		}

	public:
		/*
		頂点シェーダーを設定
		shader		頂点シェーダー
		*/
		void VSSetShader(Shader&shader)
		{
			IASetInputLayout(shader.GetInputLayout());
			m_pD3DDeviceContext->VSSetShader((ID3D11VertexShader*)shader.GetBody(), NULL, 0);
		}

		//頂点バッファを設定
		void IASetVertexBuffer(VertexBuffer& vertexBuffer)
		{
			UINT offset = 0;
			UINT stride = vertexBuffer.GetStride();		//ストライドを取得
			m_pD3DDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.GetBody(), &stride, &offset);
		}

		//インデックスバッファを設定
		void IASetIndexBuffer(IndexBuffer& indexBuffer)
		{
			IndexBuffer::EnIndexType type = indexBuffer.GetIndexType();
			m_pD3DDeviceContext->IASetIndexBuffer(
				indexBuffer.GetBody(),
				type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
				0
			);
		}

		//プリミティブのトポロジーを設定
		//topology		トポロジー
		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			m_pD3DDeviceContext->IASetPrimitiveTopology(topology);
		}

		/*
		インデックス付き描画
		indexCount		インデックスの数
		StartIndexLocation		描画を開始するインデックスの位置。大抵0で大丈夫
		BaseVertexLocation		ベース頂点インデックス。大抵0で大丈夫
		*/
		void DrawIndexed(
			_In_ UINT IndexCount,		//インデックスの数
			_In_ UINT StartIndexLocation,		//描画を開始するインデックスの位置
			_In_ INT BaseVertexLocation)		//ベース頂点インデックス
		{
			m_pD3DDeviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
		}

		/*
		描画
		vartexCount		頂点数
		startVertexLocation		描画を開始する頂点の位置。大抵0で大丈夫
		*/
		void Draw(
			unsigned int vertexCount,		//頂点数
			unsigned int startVertexLocation		//描画を開始する頂点の位置
		)
		{
			m_pD3DDeviceContext->Draw(vertexCount, startVertexLocation);
		}

	private:
		ID3D11DeviceContext* m_pD3DImmidiateDeviceContext = nullptr;
		ID3D11DeviceContext* m_pD3DDeviceContext = nullptr;		//描画コマンドを積んでいくコンテキスト。
		ID3D11RasterizerState* RasterizerState = nullptr;		//画像をビットマップにする
	};
}