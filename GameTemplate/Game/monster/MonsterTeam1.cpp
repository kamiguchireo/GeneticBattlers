#include "stdafx.h"
#include "MonsterTeam1.h"


MonsterTeam1::MonsterTeam1()
{
}


MonsterTeam1::~MonsterTeam1()
{
}

bool MonsterTeam1::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");

	return true;
}

void MonsterTeam1::Update()
{
	m_position.y = m_activeTime;
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//描画処理。
	Draw();
}

bool MonsterTeam1::Action_good()
{
	m_status.DEX += rand() % 5 - 3;

	return true;
}

bool MonsterTeam1::Action_usually()
{
	return false;
}

bool MonsterTeam1::Action_bad()
{
	return false;
}
