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
		void* pSrcVertexBuffer,
		int numIndex,
		IndexBuffer::EnIndexType indexType,
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

}