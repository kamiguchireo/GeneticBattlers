#pragma once
class SkillLog:public IGameObject
{
public:
	SkillLog();
	~SkillLog();
	bool Start();
	void Update();
	void SetText(const wchar_t* text)
	{
		m_skillText = text;
	}

	static SkillLog* GetInstance()
	{
		return m_instance;
	}
	/// <summary>
	/// MPが足りているか？足りていないならtrueをセット。
	/// </summary>
	/// <param name="flag">フラグ足りていないならtrueにしておくといい。</param>
	void SetMPShortage(bool flag)
	{
		m_isMP = flag;
	}
	//時間経過削除フラグ設定。
	void SetDelete(bool flag)
	{
		m_countDown = flag;
	}
private:
	void CreateMPLog();

private:	//定数。
	static const CVector2 SLOG_POSITION;
	static const CVector2 MPLOG_POSITION;
	static const CVector2 WINDOW_SIZE;

private:
	static SkillLog* m_instance;
	prefab::SpriteRender* m_sprite = nullptr;	//ウィンドウのスプライト。
	prefab::SpriteRender* m_mpSprite = nullptr;	//「MPが足りない」を表示するウィンドウのスプライト。
	prefab::FontRender* m_font = nullptr;		//表示するフォント。
	prefab::FontRender* m_mpLog = nullptr;		//「MPが足りない」を表示する。
	
	const wchar_t* m_skillText = nullptr;		//スキル名。

	float m_deleteTime = 0.65f;		//削除までの時間。(秒)

	bool m_isMP = false;			//MPが足ないか？
	bool m_countDown = false;		//時間経過後削除フラグ。
};

