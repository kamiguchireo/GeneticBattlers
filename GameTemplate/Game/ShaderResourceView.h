#pragma once#pragma once

namespace Engine {
	class CStructuredBuffer;
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();

		//StructuredBuffer�p��SRV���쐬
		bool Create(CStructuredBuffer&structuredBuffer);

		//DDS�t�@�C������e�N�X�`���p��SRV���쐬
		//fileName		�t�@�C����
		ID3D11ShaderResourceView* CreateFromDDSTextureFromFile(const wchar_t*fileName);

		//ID3D11DeviceContext*& GetBody()
		//{
		//	return m_srv;
		//}
		//�J������
		void Release();

		//ID3D11ShaderResourceView���擾
		ID3D11ShaderResourceView*& GetBody()
		{
			return m_srv;
		}
	private:
		std::map<std::wstring, ID3D11ShaderResourceView*> m_list;
		ID3D11ShaderResourceView* m_srv = nullptr;
		bool m_isValid = false;		//�L���ȃf�[�^���ǂ���
	};

}