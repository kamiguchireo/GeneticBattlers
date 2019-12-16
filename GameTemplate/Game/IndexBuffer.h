#pragma once

namespace Engine {
	//インデックスバッファ
	class IndexBuffer
	{
	public:

		//インデックスの型
		enum EnIndexType {
			enIndexType_16,		//16ビットインデックス。
			enIndexType_32,		//32ビットインデックス
		};
		//コンストラクタ
		IndexBuffer();
		//デストラクタ
		~IndexBuffer();
		
		/*インデックスバッファを作成
		numIndex		インデックスの数
		indexType		インデックスの型
		pSrcIndexBuffer		ソースインデックスバッファ
		*/
		bool Create(int numIndex, EnIndexType indexType, const void*pSrcIndexBuffer);

		//開放
		void Release();

	private:
		bool m_isCreated = false;		//インデックスバッファが作成されているかどうか
		ID3D11Buffer* m_indexBuffer = nullptr;		//インデックスバッファ
		EnIndexType m_indexType = enIndexType_16;		//インデックスの型
		unsigned int m_numIndex = 0;		//インデックスの数
	};

}