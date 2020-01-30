#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	/// <summary>
	/// �J�n�����B
	/// </summary>
	/// <returns>true��Ԃ����珈���I���B</returns>
	bool Start();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	void PostRender(RenderContext& renderContext);
	/// <summary>
	/// �t�F�[�h�C�����J�n����B
	/// </summary>
	void StartFadeIn()
	{
		m_state = enState_fadeIn;
	}
	/// <summary>
	/// �t�F�[�h�A�E�g���J�n����B
	/// </summary>
	void StartFadeOut()
	{
		m_state = enState_fadeOut;
	}
	/// <summary>
	/// �t�F�[�h�����ǂ����B
	/// </summary>
	/// <returns></returns>
	bool IsFade()
	{
		return m_state != enState_idle;
	}

	static Fade* GetInstance()
	{
		return m_instance;
	}
	static Fade* m_instance;
private:
	enum EnFadeState {
		enState_fadeIn,		//!<�t�F�[�h�C�����B
		enState_fadeOut,	//!<�t�F�[�h�A�E�g���B
		enState_idle		//!<�A�C�h�����B
	};
	ShaderResourceView m_texture;			//!<�V�F�[�_�[���\�[�X�r���[�B
	Sprite m_sprite;						//!<�X�v���C�g�B
	EnFadeState m_state = enState_idle;		//!<��ԁB
	float m_currentAlpha = 1.0f;			//!<���݂̃��l�B
};

