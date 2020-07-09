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

private:
	prefab::SpriteRender* m_sprite = nullptr;
	prefab::FontRender* m_font = nullptr;

	const wchar_t* m_skillText = nullptr;

	static const CVector2 LOG_POSITION;
};

