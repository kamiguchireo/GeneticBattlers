#pragma once
#include "CGPUBuffer.h"

namespace Engine {
	//定数バッファ
	//CGPUBufferを継承
	class ConstantBuffer:public CGPUBuffer
	{
	public:
		//コンストラクタ
		ConstantBuffer();
		//デストラクタ
		~ConstantBuffer();
		//ConstantBufferを作成
		//pInitData		初期データ
		//bufferSize		バッファサイズ
		bool Create(const void*pInitData, int bufferSize);
	};

}