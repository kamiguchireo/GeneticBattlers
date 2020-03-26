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
	if (!m_isEnemy) {
		DeleteGO(m_Good);
		DeleteGO(m_Bad);
	}
}

bool StatusUI::Start()
{
	m_position.z = 5.0f;
	/****************/
	/*���L�����pUI�B*/
	/****************/
	if (!m_isEnemy) {
		//���W��ݒ�B
		m_para = NewGO<prefab::SpriteRender>(0);
		m_para->Init(L"Assets/sprite/para.dds", 300.0f, 150.0f);
		m_para->SetPosition(m_position);

		//ATB�̈ʒu��ݒ�B
		CVector3 atbPos = m_position;
		atbPos.y += 40.0f;
		atbPos.x -= 100.0f;
		//ATB�Q�[�W�B
		m_ATBG = NewGO<prefab::SpriteRender>(0);
		m_ATBG->Init(L"Assets/sprite/ATBG.dds", 200.0f, 10.0f);
		m_ATBG->SetPivot({ 0.0f,0.0f });
		m_ATBG->SetPosition(atbPos);
		m_scale.x = m_scaleX;
		m_ATBG->SetScale(m_scale);
		//m_ATBG->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		//ATB�o�[�B
		m_ATB = NewGO<prefab::SpriteRender>(0);
		m_ATB->Init(L"Assets/sprite/ATB.dds", 200.0f, 10.0f);
		m_ATB->SetPivot({ 0.0f,0.0f });
		m_ATB->SetPosition(atbPos);
		m_ATB->SetScale(CVector3::One());

		//HP�o�[�̈ʒu��ݒ�B
		CVector3 hpPos = atbPos;	//ATB�̏������B
		hpPos.y -= 30.0f;
		//HP�Q�[�W�B
		m_HPG = NewGO<prefab::SpriteRender>(0);
		m_HPG->Init(L"Assets/sprite/HPG.dds", 184.0f, 20.0f);
		m_HPG->SetPivot({ 0.0f,0.0f });
		CVector3 hpgPos = hpPos;
		hpgPos.x += 8.0f;
		m_HPG->SetPosition(hpgPos);
		//HP�o�[�B
		m_HP = NewGO<prefab::SpriteRender>(0);
		m_HP->Init(L"Assets/sprite/HP.dds", 200.0f, 20.0f);
		m_HP->SetPivot({ 0.0f,0.0f });
		m_HP->SetPosition(hpPos);

		//�]���{�^���̈ʒu��ݒ�B
		const float yPos = 25.0f;
		const float xPos = 50.0f;
		//HP�Q�[�W�B
		CVector3 goodPos = m_position;
		goodPos.y -= yPos;
		goodPos.x -= xPos;
		m_Good = NewGO<prefab::SpriteRender>(0);
		m_Good->Init(L"Assets/sprite/Good.dds", 50.0f, 50.0f);
		m_Good->SetPosition(goodPos);
		m_Good->SetMulColor(m_Gray);

		//HP�o�[�B
		CVector3 badPos = m_position;
		badPos.y -= yPos;
		badPos.x += xPos;
		m_Bad = NewGO<prefab::SpriteRender>(0);
		m_Bad->Init(L"Assets/sprite/Bad.dds", 50.0f, 50.0f);
		m_Bad->SetPosition(badPos);
		m_Bad->SetMulColor(m_Gray);
	}
	/******************/
	/*�G�p��UI�̐ݒ�B*/
	/******************/
	else if (m_isEnemy) {
		//���W��ݒ�B
		m_para = NewGO<prefab::SpriteRender>(0);
		m_para->Init(L"Assets/sprite/paraE.dds", 300.0f, 75.0f);
		m_para->SetPosition(m_position);

		//ATB�̈ʒu��ݒ�B
		CVector3 atbPos = m_position;
		atbPos.y += 10.0f;
		atbPos.x -= 100.0f;
		//ATB�Q�[�W�B
		m_ATBG = NewGO<prefab::SpriteRender>(0);
		m_ATBG->Init(L"Assets/sprite/ATBG.dds", 200.0f, 10.0f);
		m_ATBG->SetPivot({ 0.0f,0.0f });
		m_ATBG->SetPosition(atbPos);
		m_scale.x = m_scaleX;
		m_ATBG->SetScale(m_scale);
		//m_ATBG->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		//ATB�o�[�B
		m_ATB = NewGO<prefab::SpriteRender>(0);
		m_ATB->Init(L"Assets/sprite/ATB.dds", 200.0f, 10.0f);
		m_ATB->SetPivot({ 0.0f,0.0f });
		m_ATB->SetPosition(atbPos);
		m_ATB->SetScale(CVector3::One());

		//HP�o�[�̈ʒu��ݒ�B
		CVector3 hpPos = atbPos;	//ATB�̏������B
		hpPos.y -= 28.0f;
		//HP�Q�[�W�B
		m_HPG = NewGO<prefab::SpriteRender>(0);
		m_HPG->Init(L"Assets/sprite/HPG.dds", 184.0f, 20.0f);
		m_HPG->SetPivot({ 0.0f,0.0f });
		CVector3 hpgPos = hpPos;
		hpgPos.x += 8.0f;
		m_HPG->SetPosition(hpgPos);
		//HP�o�[�B
		m_HP = NewGO<prefab::SpriteRender>(0);
		m_HP->Init(L"Assets/sprite/HP.dds", 200.0f, 20.0f);
		m_HP->SetPivot({ 0.0f,0.0f });
		m_HP->SetPosition(hpPos);
	}
	
	return true;
}

void StatusUI::Update()
{
	m_scale.x = m_scaleX;
	m_ATBG->SetScale(m_scale);
}
