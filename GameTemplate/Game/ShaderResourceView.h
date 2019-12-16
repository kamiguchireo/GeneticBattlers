#pragma once

namespace Engine {
	class CStructuredBuffer;
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();

		//StructuredBuffer�p��SRV���쐬
		bool Create(CStructuredBuffer&structuredBuffer);

		//�J������
		void Release();

	private:
		ID3D11ShaderResourceView* m_srv = nullptr;
		bool m_isValid = false;		//�L���ȃf�[�^���ǂ���
	};

}