#pragma once
#include "SpriteRender.h"
#include "SourceFile/graphic/Effect/CEffect.h"
#include "SourceFile/Sound/CSoundSource.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:
	//prefab::SpriteRender*m_spriteRender;	//スプライトレンダー
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);		//エフェクトを作成。
	//prefab::CSoundSource ss;		//サウンド
	SkinModel m_model;		//モデル
	SkinModel m_model2;		//モデル２



};

