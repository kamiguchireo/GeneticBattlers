#include "stdafx.h"
#include "BattleScenes.h"
#include "BattleManager.h"
#include "monster/MonsterBase.h"
//#include "monster/MonsterTeam1.h"
#include "monster/Attacker.h"
#include "monster/Healer.h"
#include "monster/Supporter.h"
#include "AIResouce.h"
#include "../TitleScene.h"
#include "../GAScenes/GAScenes.h"
#include "../NetScenes/NetScenes.h"
#include "Fade.h"
#include "GameCamera.h"
#include "Skill/SkillLog.h"

const CVector3 BattleScenes::ATTAKER = { -50.0f,-250.0f,0.0f };
const CVector3 BattleScenes::HEALER = { 350.0f,-250.0f,0.0f };
const CVector3 BattleScenes::SUPPORTER = { -450.0f,-250.0f,0.0f };
const CVector3 BattleScenes::ENEMY_ATTACKER = { -50.0f,300.0f,0.0f };
const CVector3 BattleScenes::ENEMY_HEALER = { -450.0f,300.0f,0.0f };
const CVector3 BattleScenes::ENEMY_SUPPORTER = { 350.0f,300.0f,0.0f };

BattleScenes::BattleScenes()
{

}

BattleScenes::~BattleScenes()
{
	DeleteGO(m_battleManager);
	DeleteGO(m_camera);
	DeleteGO(m_resultSprite);
	auto sLog = SkillLog::GetInstance();
	DeleteGO(sLog);
	DeleteGO(m_bgm);
}

bool BattleScenes::Start()
{
	//�l�b�g�V�[���̃|�C���^�擾�B
	m_netScenes = NetScenes::GetInstance();
	//�퓬�Ǘ��p�N���X�쐬�B
	m_battleManager = NewGO<BattleManager>(1);

	//�G�̏����L�^����N���X�B
	AIResouce* aiResouse = AIResouce::GetInstance();
	if (aiResouse == nullptr)
	{
		aiResouse = NewGO<AIResouce>(0);
	}	
	aiResouse->ClearData();

	//�J�X�P�[�h�V���h�E�͈͎̔w��B
	g_graphicsEngine->GetShadowMap()->SetRange({ 1000.0f,2000.0f,3000.0f });

	//���x���B
	m_level.Init(L"Assets/level/BattleStage.tkl",[&](LevelObjectData& objData) {
		if (wcscmp(objData.name, L"testGround") == 0)
		{
			//�w�i���f���B
			m_model.Init(L"Assets/modelData/testGround.cmo");
			m_model.SetActiveDLFlag(0);
			m_model.SetActiveRLFlag(0);
			m_model.SetShadowReciever(true);
			m_model.UpdateWorldMatrix(
				objData.position,
				objData.rotation,
				objData.scale
			);
			return true;
		}
		if (wcscmp(objData.name, L"EAttacker") == 0)
		{
			MonsterBase* monster = NewGO<Attacker>(0);
			monster->GetStatusManager()->StatusAttaker();
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			monster->SetScale(objData.scale);
			if (m_netScenes == nullptr){		//�l�b�g�ʐM�łȂ���΁B
				monster->Init("Assets/AIData/EnemyData/EnemyAttacker.bin");
			}
			else {		//�ʐM���Ă���Ȃ�B
				auto& ga = monster->GetAIManager();
				ga.SetAIData(m_netScenes->GetAttakerData());
			}
			//���L�^�B
			aiResouse->SetAttaker(monster->GetAIManager().GetAIData());
			monster->SetUIPos(ENEMY_ATTACKER);
			monster->SetIsEnemy(true);

			m_battleManager->PushBackEnemys(monster,job::enjob_Attacker);

			return true;
		}
		if (wcscmp(objData.name, L"EBuff") == 0)
		{
			MonsterBase* monster = NewGO<Supporter>(0);
			monster->GetStatusManager()->StatusSupporter();
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			monster->SetScale(objData.scale);
			if (m_netScenes == nullptr){		//�l�b�g�ʐM�łȂ���΁B
				monster->Init("Assets/AIData/EnemyData/EnemySupporter.bin");
			}
			else {		//�ʐM���Ă���Ȃ�B
				auto& ga = monster->GetAIManager();
				ga.SetAIData(m_netScenes->GetSupporterData());
			}
			//���L�^�B
			aiResouse->SetSupporter(monster->GetAIManager().GetAIData());
			monster->SetUIPos(ENEMY_SUPPORTER);
			monster->SetIsEnemy(true);

			m_battleManager->PushBackEnemys(monster,job::enjob_Supotter);


			return true;
		}
		if (wcscmp(objData.name, L"EHealer") == 0)
		{
			MonsterBase* monster = NewGO<Healer>(0);
			monster->GetStatusManager()->StatusHealer();
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			monster->SetScale(objData.scale);
			if (m_netScenes == nullptr){		//�l�b�g�ʐM�łȂ���΁B
				monster->Init("Assets/AIData/EnemyData/EnemyHealer.bin");
			}
			else {		//�ʐM���Ă���Ȃ�B
				auto& ga = monster->GetAIManager();
				ga.SetAIData(m_netScenes->GetHealerData());
			}
			//���L�^�B
			aiResouse->SetHealer(monster->GetAIManager().GetAIData());
			monster->SetUIPos(ENEMY_HEALER);
			monster->SetIsEnemy(true);

			m_battleManager->PushBackEnemys(monster,job::enjob_Healer);


			return true;
		}
		if (wcscmp(objData.name, L"Attacker") == 0)
		{
			MonsterBase* attacker = NewGO<Attacker>(0); 
			attacker->GetStatusManager()->StatusAttaker();
			attacker->SetPosition(objData.position);
			attacker->SetRotation(objData.rotation);
			attacker->SetScale(objData.scale);
			attacker->Init("Assets/AIData/Attacker.bin");
			attacker->SetUIPos(ATTAKER);
			m_battleManager->PushBackTeams(attacker,job::enjob_Attacker);

			return true;
		}	
		if (wcscmp(objData.name, L"Healer") == 0)
		{
			MonsterBase* healer = NewGO<Healer>(0);
			healer->GetStatusManager()->StatusHealer();
			healer->SetPosition(objData.position);
			healer->SetRotation(objData.rotation);
			healer->SetScale(objData.scale);
			healer->Init("Assets/AIData/Healer.bin");
			healer->SetUIPos(HEALER);
			m_battleManager->PushBackTeams(healer,job::enjob_Healer);
		
			return true;
		}
		if (wcscmp(objData.name, L"Buff") == 0)
		{
			MonsterBase* support = NewGO<Supporter>(0);
			support->GetStatusManager()->StatusSupporter();
			support->SetPosition(objData.position);
			support->SetRotation(objData.rotation);
			support->SetScale(objData.scale);
			support->Init("Assets/AIData/Supporter.bin");
			support->SetUIPos(SUPPORTER);
			m_battleManager->PushBackTeams(support,job::enjob_Supotter);
		
			return true;
		}


		return false;
		});
	m_battleManager->SetScenePointa(this);
	m_battleManager->SetIsBattle(false);
	//�J�����B
	m_camera = NewGO<GameCamera>(0);
	//bgm
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/bgm/bgm_battle.wav");
	m_bgm->Play(true);
	m_bgm->SetVolume(m_bgmVol);

	//�t�F�[�h�B
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	DeleteGO(m_netScenes);

	return true;
}

void BattleScenes::Update()
{
	//rand();
	switch (m_state)
	{
	case enState_FadeIn:
		if (m_bgmVol < 1.0f) {
			m_bgmVol += g_gameTime.GetFrameDeltaTime();
			m_bgmVol = min(1.0f, m_bgmVol);
		}
		if (!m_fade->IsFade()) {
			m_state = enState_Battle;
			//�퓬�J�n�B
			m_battleManager->SetIsBattle(true);
		}
		break;
	case enState_Battle:
		if (g_pad[0].IsTrigger(enButtonStart)) 
		{
			//�퓬���f�B
			m_battleManager->SetIsBattle(false);
			//�t�F�[�h������B
			m_state = enState_FadeOut; 
			m_fade->StartFadeOut();
		}
		break;

	case enState_Result:
		battleCoolTime -= g_gameTime.GetFrameDeltaTime();
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
			//�퓬�㏈���B
			m_battleManager->SaveData();		//�s���f�[�^�̍X�V�ƕۑ��B

			////�퓬�V�[���̍폜�B
			//DeleteGO(m_battleManager);
			//m_battleManager = nullptr;

			//�t�F�[�h������B
			m_state = enState_FadeOut;
			m_fade->StartFadeOut();
		}

		break;

	case enState_FadeOut:
		//bgm�̃t�F�[�h�A�E�g�B
		if (m_bgmVol > 0.0f) {
			m_bgmVol -= g_gameTime.GetFrameDeltaTime();
			m_bgmVol = max(0.0f, m_bgmVol);
		}
		if (!m_fade->IsFade())
		{
			//�t�F�[�h���I���ƃ^�C�g���ɖ߂�B
			//NewGO<TitleScene>(0, nullptr);
			NewGO<GAScenes>(0, nullptr);
			DeleteGO(this);
		}
		break;
	}

	m_bgm->SetVolume(m_bgmVol*SOUND_VOL);
	////���x���̕`��B
	//m_level.Draw();
}

void BattleScenes::Draw()
{
	//�����ŌĂ�ł�ƃQ�[�����[�v�ł��Ȃ��񂾂��B
	auto shadowMap = g_graphicsEngine->GetShadowMap();
	shadowMap->Update(CVector3::AxisY()*1000.0f + CVector3::AxisX()*200.0f, CVector3::Zero());
	shadowMap->SendShadowRecieverParamToGpu();
	shadowMap->RenderToShadowMap();
	//�X�e�[�W��\��������B
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}

