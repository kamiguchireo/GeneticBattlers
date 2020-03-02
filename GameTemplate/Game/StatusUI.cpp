#include "stdafx.h"
#include "StatusUI.h"

StatusUI::StatusUI()
{
}

StatusUI::~StatusUI()
{
	DeleteGO(m_ATB);
	DeleteGO(m_ATBG);
}

bool StatusUI::Start()
{
	m_ATBG = NewGO<prefab::SpriteRender>(0);
	m_ATBG->Init(L"Assets/sprite/ATBG.dds", 200.0f, 20.0f);
	m_ATBG->SetPivot({ 0.0f,0.0f });
	m_position.z = 5.0f;
	m_ATBG->SetPosition(m_position);
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
	m_ATBG->SetMulColor({ 0.0f,1.0f,1.0f,1.0f });
	m_ATB = NewGO<prefab::SpriteRender>(0);
	m_ATB->Init(L"Assets/sprite/ATB.dds", 200.0f, 20.0f);
	m_ATB->SetPivot({ 0.0f,0.0f });
	m_ATB->SetPosition(m_position);
	m_ATB->SetScale(CVector3::One());

	return true;
}

void StatusUI::Update()
{
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
}
