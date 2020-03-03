#include "stdafx.h"
#include "StatusUI.h"

StatusUI::StatusUI()
{
}

StatusUI::~StatusUI()
{
	DeleteGO(m_para);
	DeleteGO(m_ATB);
	DeleteGO(m_ATBG);
}

bool StatusUI::Start()
{
	m_position.z = 5.0f;

	m_para = NewGO<prefab::SpriteRender>(0);
	m_para->Init(L"Assets/sprite/para.dds", 300.0f, 150.0f);
	m_para->SetPosition(m_position);

	//ç¿ïWÇê›íËÅB
	CVector3 atbPos = m_position;
	atbPos.y += 40.0f;
	atbPos.x -= 100.0f;
	m_ATBG = NewGO<prefab::SpriteRender>(0);
	m_ATBG->Init(L"Assets/sprite/ATBG.dds", 200.0f, 10.0f);
	m_ATBG->SetPivot({ 0.0f,0.0f });
	m_ATBG->SetPosition(atbPos);
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
	//m_ATBG->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_ATB = NewGO<prefab::SpriteRender>(0);
	m_ATB->Init(L"Assets/sprite/ATB.dds", 200.0f, 10.0f);
	m_ATB->SetPivot({ 0.0f,0.0f });
	m_ATB->SetPosition(atbPos);
	m_ATB->SetScale(CVector3::One());

	return true;
}

void StatusUI::Update()
{
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
}
