#pragma once

#include "graphics/Shader.h"

/*!
*@brief	モデルエフェクト。
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<マテリアル名。
	Shader* m_pVSShader = nullptr;
	Shader* m_pPSShader = nullptr;
	Shader m_vsShader;
	Shader m_psShader;
	Shader m_psSilhouette;		//シルエット描画用のピクセルシェーダー。
	Shader m_psShadowMap;		//シャドウマップ生成用のピクセルシェーダー
	Shader m_vsShadowMap;		//シャドウマップ生成用の頂点シェーダー
	bool isSkining;
	ID3D11ShaderResourceView* m_albedoTex = nullptr;
	ID3D11ShaderResourceView* m_shadow = nullptr;
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//シルエット描画用のデプスステンシルステート。

public:
	ModelEffect()
	{
		//通常レンダリング用のピクセルシェーダーをロード
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
		//シルエット用のピクセルシェーダーをロード
		m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
		//シャドウマップ用のシェーダーをロード
		m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
		//デプスステンシルの初期化。
		InitSilhouettoDepthStepsilState();

		m_pPSShader = &m_psShader;
	}
	virtual ~ModelEffect()
	{
		if (m_albedoTex) {
			m_albedoTex->Release();
		}
		if (m_silhouettoDepthStepsilState != nullptr) {
			m_silhouettoDepthStepsilState->Release();
		}
	}
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;

	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* tex)
	{
		m_albedoTex = tex;
	}
	void SetMatrialName(const wchar_t* matName)
	{
		m_materialName = matName;
	}
	
	bool EqualMaterialName(const wchar_t* name) const
	{
		return wcscmp(name, m_materialName.c_str()) == 0;
	}

	void SetRenderMode(int renderMode)
	{
		m_renderMode = renderMode;
	}

	void SetActiveShadow(bool IsShadow)
	{
		IsActiveShadow = IsShadow;
	}
private:
	void InitSilhouettoDepthStepsilState();
	int m_renderMode = 0;
	bool IsActiveShadow = false;
};
/*!
*@brief
*  スキンなしモデルエフェクト。
*/
class NonSkinModelEffect : public ModelEffect {
public:
	NonSkinModelEffect()
	{
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = false;
	}
};
/*!
*@brief
*  スキンモデルエフェクト。
*/
class SkinModelEffect : public ModelEffect {
public:
	SkinModelEffect()
	{
		wchar_t hoge[256];
		GetCurrentDirectoryW(256, hoge);
		m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", Shader::EnType::VS);
		m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMapSkin", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = true;
	}

};

/*!
*@brief
*  エフェクトファクトリ。
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//スキニングあり。
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//スキニングなし。
			effect = std::make_shared<NonSkinModelEffect>();
		}
		effect->SetMatrialName(info.name);
		if (info.diffuseTexture && *info.diffuseTexture)
		{
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
		}
		return effect;
	}

	void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
	{
		return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
	}


};
