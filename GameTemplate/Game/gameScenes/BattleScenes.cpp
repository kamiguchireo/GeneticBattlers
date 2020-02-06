#include "stdafx.h"
#include "BattleScenes.h"
#include "monster/MonsterBase.h"
#include "monster/MonsterTeam1.h"
#include "Fade.h"
#include "TitleScene.h"

BattleScenes::BattleScenes()
{

}

BattleScenes::~BattleScenes()
{
	for (auto i : m_monsterTeam1List)
	{
		DeleteGO(i);
	}
}

bool BattleScenes::Start()
{
	InitMonster();

	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	return true;
}

void BattleScenes::Update()
{
	switch (m_state)
	{
	case enState_FadeIn:
		if (!m_fade->IsFade())
		{
			m_state = enState_Battle;
		}
		break;
	case enState_Battle:
		ActiveTimeUpdate();
		MonsterAction();
		if (g_pad[0].IsTrigger(enButtonStart))
		{
			m_state = enState_FadeOut;
			m_fade->StartFadeOut();
		}
		break;
	case enState_FadeOut:
		if (!m_fade->IsFade())
		{
			TitleScene* t = NewGO<TitleScene>(0, nullptr);
			DeleteGO(this);
		}
	}

}

void BattleScenes::InitMonster()
{
	const int MonsterNum = 3;

	for (int i = 0; i < MonsterNum; i++) {
		CVector3 pos(-50.0f + 50.0f*i, 0.0f, 0.0f);
		Status hoge;
		hoge.HP = rand() % 50 + 100;
		hoge.MP = rand() % 50 + 100;
		hoge.ATK = rand() % 10 + 10;
		hoge.DEF = rand() % 10 + 10;
		hoge.MAT = rand() % 10 + 10;
		hoge.MDF = rand() % 10 + 10;
		hoge.DEX = rand() % 10 + 10;
		MonsterBase* monster = NewGO<MonsterTeam1>(0);
		monster->SetPosition(pos);
		monster->SetStatus(hoge);
		m_monsterTeam1List.push_back(monster);
	}
}

void BattleScenes::MonsterAction()
{
	//�N���s�����Ă��Ȃ��Ȃ璆�f�B
	if (m_monsterACT == nullptr)return;

	//�s�����I���܂ōs����������B
	bool is_playAction = m_monsterACT->Action();

	//�s�����I�������|�C���^��null������B
	if (is_playAction) {
		m_monsterACT = nullptr;

		//�c��HP�ɉ����ăX�e�[�g���X�V�B
		for (int i = 0; i < m_monsterTeam1List.size(); i++) {
			m_monsterTeam1List[i]->StateUpdate();
		}
	}
}

void BattleScenes::ActiveTimeUpdate()
{
	//�s�����Ȃ璆�f�B
	if (m_monsterACT != nullptr)return;

	//�S���̃^�C���Q�[�W�����Z���Ă����B
	for (int i = 0; i < m_monsterTeam1List.size(); i++)
	{
		bool is_action = m_monsterTeam1List[i]->AddATB();

		//�Q�[�W�����܂�؂�����|�C���^���擾����B�@
		if (is_action) {
			m_monsterACT = m_monsterTeam1List[i];
			m_monsterACT->SelectUseSkill(m_monsterTeam1List);
		}
	}
}
