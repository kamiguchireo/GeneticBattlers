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
		ID3D11ShaderResourceView* CreateFromDDSTextureFromFile(const wchar_t*fileName);

		//ID3D11DeviceContext*& GetBody()
		//{
		//	return m_srv;
		//}
		//開放処理
		void Release();

		//ID3D11ShaderResourceViewを取得
		ID3D11ShaderResourceView*& GetBody()
		{
			return m_srv;
		}
	private:
		std::map<std::wstring, ID3D11ShaderResourceView*> m_list;
		ID3D11ShaderResourceView* m_srv = nullptr;
		bool m_isValid = false;		//有効なデータかどうか
	};

}