#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	/// <summary>
	/// 開始処理。
	/// </summary>
	/// <returns>trueを返したら処理終了。</returns>
	bool Start();
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update();
	void PostRender(RenderContext& renderContext);
	/// <summary>
	/// フェードインを開始する。
	/// </summary>
	void StartFadeIn()
	{
		m_state = enState_fadeIn;
	}
	/// <summary>
	/// フェードアウトを開始する。
	/// </summary>
	void StartFadeOut()
	{
		m_state = enState_fadeOut;
	}
	/// <summary>
	/// フェード中かどうか。
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
		enState_fadeIn,		//!<フェードイン中。
		enState_fadeOut,	//!<フェードアウト中。
		enState_idle		//!<アイドル中。
	};
	ShaderResourceView m_texture;			//!<シェーダーリソースビュー。
	Sprite m_sprite;						//!<スプライト。
	EnFadeState m_state = enState_idle;		//!<状態。
	float m_currentAlpha = 1.0f;			//!<現在のα値。
};

