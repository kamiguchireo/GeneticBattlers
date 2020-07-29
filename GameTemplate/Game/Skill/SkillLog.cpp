#include "stdafx.h"
#include "SkillLog.h"

const CVector2 SkillLog::LOG_POSITION = { 0.0f,220.0f};
SkillLog* SkillLog::m_instance = nullptr;

SkillLog::SkillLog()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
	}
	else
	{
		DeleteGO(this);
	}
}

SkillLog::~SkillLog()
{
	DeleteGO(m_font);
	DeleteGO(m_sprite);

	if (m_instance == this)
	{
		m_instance = nullptr;
	}
}

bool SkillLog::Start()
{
	m_sprite = NewGO<prefab::SpriteRender>(3);
	m_sprite->Init(
		L"Assets/sprite/BackWindow.dds",
		300,
		75
	);
	m_sprite->SetPosition({ 
		LOG_POSITION.x,
		LOG_POSITION.y,
		5.0f 
		});
	m_sprite->SetPivot({ 0.5f,0.5f });

	m_font = NewGO<prefab::FontRender>(3);
	m_font->SetText(m_skillText);
	m_font->SetPosition(LOG_POSITION);
	m_font->SetPivot({ 0.5f,0.5f });
	m_font->SetScale(0.75f);			//文字サイズ変更。

	return true;
}

void SkillLog::Update()
{
}
