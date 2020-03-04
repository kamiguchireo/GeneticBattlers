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
	DeleteGO(m_HP);
	DeleteGO(m_HPG);
}

bool StatusUI::Start()
{
	m_position.z = 5.0f;
	
	//座標を設定。
	m_para = NewGO<prefab::SpriteRender>(0);
	m_para->Init(L"Assets/sprite/para.dds", 300.0f, 150.0f);
	m_para->SetPosition(m_position);

	//ATBの位置を設定。
	CVector3 atbPos = m_position;
	atbPos.y += 40.0f;
	atbPos.x -= 100.0f;
	//ATBゲージ。
	m_ATBG = NewGO<prefab::SpriteRender>(0);
	m_ATBG->Init(L"Assets/sprite/ATBG.dds", 200.0f, 10.0f);
	m_ATBG->SetPivot({ 0.0f,0.0f });
	m_ATBG->SetPosition(atbPos);
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
	//m_ATBG->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	//ATBバー。
	m_ATB = NewGO<prefab::SpriteRender>(0);
	m_ATB->Init(L"Assets/sprite/ATB.dds", 200.0f, 10.0f);
	m_ATB->SetPivot({ 0.0f,0.0f });
	m_ATB->SetPosition(atbPos);
	m_ATB->SetScale(CVector3::One());

	//HPバーの位置を設定。
	CVector3 hpPos = atbPos;	//ATBの少し下。
	hpPos.y -= 30.0f;
	//HPゲージ。
	m_HPG = NewGO<prefab::SpriteRender>(0);
	m_HPG->Init(L"Assets/sprite/HPG.dds", 184.0f, 20.0f);
	m_HPG->SetPivot({ 0.0f,0.0f });
	CVector3 hpgPos = hpPos;
	hpgPos.x += 8.0f;
	m_HPG->SetPosition(hpgPos);
	//HPバー。
	m_HP = NewGO<prefab::SpriteRender>(0);
	m_HP->Init(L"Assets/sprite/HP.dds", 200.0f, 20.0f);
	m_HP->SetPivot({ 0.0f,0.0f });
	m_HP->SetPosition(hpPos);


	return true;
}

void StatusUI::Update()
{
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
}
