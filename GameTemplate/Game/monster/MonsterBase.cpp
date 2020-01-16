#include "stdafx.h"
#include "MonsterBase.h"
#include "SkillList.h"


MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}

void MonsterBase::SetStatus(int hp, int mp, int atk, int def, int mat, int mdf, int dex)
{
	m_status.MAXHP = hp;
	m_status.HP = m_status.MAXHP;
	m_status.MAXMP = mp;
	m_status.MP = m_status.MAXMP;
	m_status.ATK = atk;
	m_status.DEF = def;
	m_status.MAT = mat;
	m_status.MDF = mdf;
	m_status.DEX = dex;
}

void MonsterBase::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void MonsterBase::Action()
{
	//c‚èHP‚É‰‚¶‚Äs“®‚ğŒˆ‚ß‚éB
	switch (m_stateAI)
	{
	case en_state_Good:
		break;
	
	case en_state_Usually:
		break;
	
	case en_state_Bad:
		break;
	
	case en_state_Death:
		break;
	}
}
