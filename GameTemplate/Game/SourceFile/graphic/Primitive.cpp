#include "stdafx.h"
#include "Primitive.h"

namespace Engine {
	Primitive::Primitive()
	{
	}
	Primitive::~Primitive()
	{
	}

	void Primitive::Release()
	{
		//頂点バッファの開放処理
		m_vertexBuffer.Release();
		//インデックスバッファの開放処理
		m_indexBuffer.Release();
	}
	bool Primitive::Create(
		D3D_PRIMITIVE_TOPOLOGY  topology,
		int numVertex,
		int vertexStride,
		//頂点バッファへのポインタ
		void* pSrcVertexBuffer,
		//インデックスの数
		int numIndex,
		//インデックスの型
		IndexBuffer::EnIndexType indexType,
		//インデックスバッファへのポインタ
		void* pSrcIndexBuffer)
	{
		//中身があるかもしれないから開放処理を行う
		Release();
		m_topology = topology;
		//頂点バッファのCreate
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcIndexBuffer);
		if (!result)
		{
			//失敗したらfalseを返す
			return false;
		}
		if (pSrcIndexBuffer)
		{
			//インデックスバッファのCreate
			result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
			if (!result)
			{
				//失敗したらfalseを返す
				return false;
			}
		}
		//成功したらtrueを返す
		return true;
	}

	//描画
	void Primitive::Draw(RenderContext& rc)
	{
		//頂点バッファを設定。
		rc.IASetVertexBuffer(m_vertexBuffer);
		//インデックスバッファを設定
		rc.IASetIndexBuffer(m_indexBuffer);
		//プリミティブのトポロジーを設定。
		rc.IASetPrimitiveTopology(m_topology);
		//描画。
		rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}

	//描画
	void Primitive::Draw(RenderContext& rc, int numVertex)
	{
		rc.IASetVertexBuffer(m_vertexBuffer);
		//プリミティブのトポロジーを設定。
		rc.IASetPrimitiveTopology(m_topology);
		//描画。
		rc.Draw(numVertex, 0);
	}

}