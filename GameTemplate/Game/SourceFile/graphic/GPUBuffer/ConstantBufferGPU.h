#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	class ConstantBufferGPU:Engine::Noncopyable
	{
	public:
		ConstantBufferGPU();
		~ConstantBufferGPU();

		//VRAM上に定数バッファを作成する
		//pInitData		初期化データ	nullptrを指定した場合は、未初期化の定数バッファが作成されます。
		//bufferSize		作成するバッファのサイズ
		//この関数内で16バイトアライメントに切り上げされる
		void Create(const void* pInitData,int bufferSize);

		//定数バッファを取得
		ID3D11Buffer* GetD3D11Buffer()const
		{
			return m_constantBuffer;
		}

	private:
		ID3D11Buffer* m_constantBuffer = nullptr;		//GPUBuffer上の定数バッファ
	};
}
