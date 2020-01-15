#pragma once

namespace Engine {
	//GPUバッファー
	class CGPUBuffer
	{
	public:
		CGPUBuffer();
		virtual ~CGPUBuffer();

		//GPUBufferを作成
		//pInitData		初期データ
		//bufferDesc		バッファ定義
		bool Create(const void*pInitData, D3D11_BUFFER_DESC& bufferDesc);

		//ID3D11Bufferのポインタを取得
		ID3D11Buffer*& GetBody()
		{
			return m_gpuBuffer;
		}

		//開放処理
		//デストラクタからもコールされている
		//明示的なタイミングで開放したい場合に呼び出して！
		void Release();

	private:
		//GPUBuffer
		ID3D11Buffer* m_gpuBuffer = nullptr;	
	};

}