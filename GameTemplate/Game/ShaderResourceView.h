#pragma once#pragma once

namespace Engine {
	class CStructuredBuffer;
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();

		//StructuredBuffer用のSRVを作成
		bool Create(CStructuredBuffer&structuredBuffer);

		//DDSファイルからテクスチャ用のSRVを作成
		//fileName		ファイル名
		bool CreateFromDDSTextureFromFile(const wchar_t*fileName);

		//開放処理
		void Release();

	private:
		ID3D11Device*m_pd3dDevice;
		ID3D11ShaderResourceView* m_srv = nullptr;
		bool m_isValid = false;		//有効なデータかどうか
	};

}