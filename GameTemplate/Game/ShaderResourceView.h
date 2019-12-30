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
		bool CreateFromDDSTextureFromFile(const wchar_t*fileName);

		//�J������
		void Release();

	private:
		ID3D11Device*m_pd3dDevice;
		ID3D11ShaderResourceView* m_srv = nullptr;
		bool m_isValid = false;		//�L���ȃf�[�^���ǂ���
	};

}