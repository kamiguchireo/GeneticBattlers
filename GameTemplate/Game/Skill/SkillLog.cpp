#include "stdafx.h"
#include "SkillLog.h"

const CVector2 SkillLog::SLOG_POSITION = { 0.0f,230.0f};
const CVector2 SkillLog::MPLOG_POSITION = { 0.0f,170.0f};
const CVector2 SkillLog::WINDOW_SIZE = { 300.0f,60.0f };
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
	DeleteGO(m_mpLog);
	DeleteGO(m_sprite);
	DeleteGO(m_mpSprite);

	if (m_instance == this)
	{
		m_instance = nullptr;
	}
}

bool SkillLog::Start()
{
	m_sprite = NewGO<prefab::SpriteRender>(3);
	if (m_isUseEnemy)
	{
		//使用者が敵。
		m_sprite->Init(
			L"Assets/sprite/BackWindowR.dds",
			WINDOW_SIZE.x,
			WINDOW_SIZE.y
		);
	}
	else
	{
		//使用者が味方。
		m_sprite->Init(
			L"Assets/sprite/BackWindow.dds",
			WINDOW_SIZE.x,
			WINDOW_SIZE.y
		);
	}
	m_sprite->SetPosition({ 
		SLOG_POSITION.x,
		SLOG_POSITION.y,
		5.0f 
		});
	m_sprite->SetPivot({ 0.5f,0.5f });

	m_font = NewGO<prefab::FontRender>(3);
	m_font->SetText(m_skillText);
	m_font->SetPosition(SLOG_POSITION);
	m_font->SetPivot({ 0.5f,0.5f });
	m_font->SetScale(0.75f);			//文字サイズ変更。

	//MPが足りてないログ表示。
	if (m_isMP)
	{
		CreateMPLog();
	}

	return true;
}

void SkillLog::Update()
{
	if (m_countDown && m_isMP)
	{
		//時間が経過したら。
		if (m_deleteTime > 0.0f)
		{
			m_deleteTime -= g_gameTime.GetFrameDeltaTime();
		}
		else {
			DeleteGO(this);
		}
	}
	else if (m_countDown)
	{
		DeleteGO(this);
	}
}

void SkillLog::CreateMPLog()
{
	m_mpSprite = NewGO<prefab::SpriteRender>(3);
	if (m_isUseEnemy)
	{
		//使用者が敵。
		m_mpSprite->Init(
			L"Assets/sprite/BackWindowR.dds",
			WINDOW_SIZE.x,
			WINDOW_SIZE.y
		);
	}
	else
	{
		//使用者が味方。
		m_mpSprite->Init(
			L"Assets/sprite/BackWindow.dds",
			WINDOW_SIZE.x,
			WINDOW_SIZE.y
		);
	}
	m_mpSprite->SetPosition({
		MPLOG_POSITION.x,
		MPLOG_POSITION.y,
		5.0f
		});
	m_mpSprite->SetPivot({ 0.5f,0.5f });

	m_mpLog = NewGO<prefab::FontRender>(3);
	m_mpLog->SetText(L"MPが足りない");
	m_mpLog->SetPosition(MPLOG_POSITION);
	m_mpLog->SetPivot({ 0.5f,0.5f });
	m_mpLog->SetScale(0.75f);			//文字サイズ変更。
}
