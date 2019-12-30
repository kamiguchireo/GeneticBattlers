#include "stdafx.h"
#include "ConstantBuffer.h"


namespace Engine {
	//コンストラクタ
	ConstantBuffer::ConstantBuffer()
	{
	}
	//デストラクタ
	ConstantBuffer::~ConstantBuffer()
	{
	}
	
	//ConstantBufferを作成
	//pInitData		初期データ
	//bufferSize		バッファサイズ
	bool ConstantBuffer::Create(const void*pInitData, int bufferSize)
	{
		//ConstantBuffer用のバッファ定義を作成する。
		//バッファリソースを作成するために使われる
		D3D11_BUFFER_DESC bufferDesc;
		//bufferDescのメモリに0を代入する
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		//バッファーで想定されている読み込み及び書き込みの方法
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//バッファーのサイズ
		//16倍とアライメントに切り上げる
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
		//バッファーをどのようにパイプラインにバインド(関連付ける)
		//かを識別する
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//CPUアクセスのフラグ
		//CPUアクセスが必要でない場合は0になる
		bufferDesc.CPUAccessFlags = 0;
		//
		return CGPUBuffer::Create(pInitData, bufferDesc);
	}
}