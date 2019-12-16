#pragma once

namespace Engine {
	class CStructuredBuffer;
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();

		//StructuredBuffer用のSRVを作成
		bool Create(CStructuredBuffer&structuredBuffer);

		//開放処理
		void Release();

	private:
		ID3D11ShaderResourceView* m_srv = nullptr;
		bool m_isValid = false;		//有効なデータかどうか
	};

}