#include "stdafx.h"
#include "BattleScenes.h"
#include "monster/MonsterBase.h"
#include "monster/MonsterTeam1.h"
#include "monster/Attacker.h"
#include "monster/Healer.h"
#include "monster/Supporter.h"
#include "../TitleScene.h"
#include "Fade.h"
#include "GameCamera.h"

BattleScenes::BattleScenes()
{

}

BattleScenes::~BattleScenes()
{
	DeleteGO(m_camera);
	DeleteGO(m_resultSprite);
	for (int i = 0; i < m_monsterTeam1List.size(); i++)
	{
		DeleteGO(m_monsterTeam1List[i]);
	}
	for (int i = 0; i < m_monsterTeam2List.size(); i++)
	{
		DeleteGO(m_monsterTeam2List[i]);
	}
}

bool BattleScenes::Start()
{
	//���x���B
	m_level.Init(L"Assets/level/testStage.tkl",[&](LevelObjectData& objData) {
		if (wcscmp(objData.name, L"testGround") == 0)
		{
			m_model.Init(L"Assets/modelData/testGround.cmo");
			m_model.SetActiveDLFlag(1);
			m_model.SetActiveRLFlag(0);
			m_model.UpdateWorldMatrix(
				objData.position,
				objData.rotation,
				CVector3::One()
			);
			return true;
		}
		if (wcscmp(objData.name, L"testModel") == 0)
		{
			MonsterBase* monster = NewGO<MonsterTeam1>(0);
			Status hoge;
			hoge.HP = rand() % 50 + 100;
			hoge.ATK = rand() % 10 + 10;
			hoge.DEF = rand() % 10 + 10;
			hoge.MAT = rand() % 10 + 10;
			hoge.MDF = rand() % 10 + 10;
			hoge.DEX = rand() % 10 + 10;
			monster->SetStatus(hoge);
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			m_monsterTeam2List.push_back(monster);

			CVector3 uipos = { objData.position.x / -2.5f - 50.0f,300.0f,0.0f };
			monster->SetUIPos(uipos);

			return true;
		}
		if (wcscmp(objData.name, L"Attacker") == 0)
		{
			MonsterBase* attacker = NewGO<Attacker>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 300;
			hoge.DEF = 10;
			hoge.MAT = 5;
			hoge.MDF = 10;
			hoge.DEX = 10;
			attacker->SetStatus(hoge);
			attacker->SetPosition(objData.position);
			attacker->SetRotation(objData.rotation);
			attacker->Init("Assets/AIData/Attacker.bin");
			m_monsterTeam1List.push_back(attacker);

			return true;
		}	
		if (wcscmp(objData.name, L"Healer") == 0)
		{
			MonsterBase* healer = NewGO<Healer>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 10;
			hoge.MAT = 30;
			hoge.MDF = 20;
			hoge.DEX = 10;
			healer->SetStatus(hoge);
			healer->SetPosition(objData.position);
			healer->SetRotation(objData.rotation);
			healer->Init("Assets/AIData/Healer.bin");
			m_monsterTeam1List.push_back(healer);
		
			return true;
		}
		if (wcscmp(objData.name, L"Buff") == 0)
		{
			MonsterBase* support = NewGO<Supporter>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 15;
			hoge.MAT = 20;
			hoge.MDF = 15;
			hoge.DEX = 15;
			support->SetStatus(hoge);
			support->SetPosition(objData.position);
			support->SetRotation(objData.rotation);
			support->Init("Assets/AIData/Supporter.bin");
			m_monsterTeam1List.push_back(support);
		
			return true;
		}


		return false;
		});

	for (int i = 0; i < m_monsterTeam1List.size(); i++)
	{
		m_monsterTeam1List[i]->SetTeamMenber(m_monsterTeam1List);
	}
	for (int i = 0; i < m_monsterTeam2List.size(); i++)
	{
		m_monsterTeam2List[i]->SetTeamMenber(m_monsterTeam2List);
	}

	//�J�����B
	m_camera = NewGO<GameCamera>(0);
	//�t�F�[�h�B
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	return true;
}

void BattleScenes::Update()
{
	rand();
	switch (m_state)
	{
	case enState_FadeIn:
		if (!m_fade->IsFade())	m_state = enState_Battle;
		break;
	case enState_Battle:
		switch (m_battleState)
		{
		//�A�N�e�B�u�^�C�������Z�B
		case enState_ATB:
			//ActiveTimeUpdate();
			break;
		//�s���������s���B
		case enState_ACT:
			//MonsterAction();
			break;
		//�]���������s���B
		case enState_Scoring:
			MonsterScoring();
			break;

		default:
			break;
		}

		if (g_pad[0].IsTrigger(enButtonStart)) 
		{
			//�t�F�[�h������B
			m_state = enState_FadeOut; 
			m_fade->StartFadeOut();
		}
		break;

	case enState_Result:
		battleCoolTime -= 1.0f / 72.0f;
		if (battleCoolTime > 0.0f) {
			break;
		}
		if (m_isWin && !m_isSprite) {
			//�����I
			m_resultSprite = NewGO<prefab::SpriteRender>(0);
			m_resultSprite->Init(L"Assets/sprite/win.dds",600.0f,400.0f);
			m_isSprite = true;
		}
		else if (!m_isWin && !m_isSprite) {
			//�s�k�B
			m_resultSprite = NewGO<prefab::SpriteRender>(0);
			m_resultSprite->Init(L"Assets/sprite/lose.dds",600.0f,400.0f);
			m_isSprite = true;
		}

		
		if (g_pad[0].IsTrigger(enButtonA))
		{
			for (int i = 0; i < m_monsterTeam1List.size(); i++)
			{
				//m_monsterTeam1List[i]->Save();
			}
			//�t�F�[�h������B
			m_state = enState_FadeOut;
			m_fade->StartFadeOut();
		}

		break;

	case enState_FadeOut:
		if (!m_fade->IsFade())
		{
			//�t�F�[�h���I���ƃ^�C�g���ɖ߂�B
			NewGO<TitleScene>(0, nullptr);
			DeleteGO(this);
		}
		break;
	}

	//�X�e�[�W��\��������B
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	//���x���̕`��B
	m_level.Draw();
}

void BattleScenes::InitMonster()
{
	const int MonsterNum = 3;

	for (int i = 0; i < MonsterNum; i++) {
		MonsterBase* monster = NewGO<MonsterTeam1>(0);
		CVector3 pos(-50.0f + 50.0f*i, 0.0f, 0.0f);
		Status hoge;
		hoge.HP = rand() % 50 + 100;
		//hoge.MP = rand() % 50 + 100;
		hoge.ATK = rand() % 10 + 10;
		hoge.DEF = rand() % 10 + 10;
		hoge.MAT = rand() % 10 + 10;
		hoge.MDF = rand() % 10 + 10;
		hoge.DEX = rand() % 10 + 10;
		monster->SetPosition(pos);
		monster->SetStatus(hoge);
		m_monsterTeam1List.push_back(monster);
	}
}


void BattleScenes::MonsterScoring()
{
	bool flag = m_monsterACT->ACTScoring();

	if (flag) {
		//�s�����I�������|�C���^��null������B
		m_monsterACTList.erase(m_monsterACTList.begin());
		m_monsterACT = nullptr;


		int myDeath = 0;
		int eneDeath = 0;

		//�f�X�����J�E���g����B
		for (int i = 0; i < m_monsterTeam1List.size(); i++) {
			if (m_monsterTeam1List[i]->IsDeath())myDeath++;
		}
		for (int i = 0; i < m_monsterTeam2List.size(); i++) {
			if (m_monsterTeam2List[i]->IsDeath())eneDeath++;
		}
		//�ǂ��炩���S�ł���΃��U���g��
		if (myDeath == m_monsterTeam1List.size()) {
			m_isWin = false;
			m_state = enState_Result;
			battleCoolTime = 3.0f;
			return;
		}	
		else if (eneDeath == m_monsterTeam2List.size()) {
			m_isWin = true;
			m_state = enState_Result;
			battleCoolTime = 1.0f;
			return;
		}

		//�N���s�����Ă��Ȃ��Ȃ�
		if (m_monsterACTList.size() == 0) {
			m_battleState = enState_ATB;
		}
		else {
			m_battleState = enState_ACT;
		}

	}
}