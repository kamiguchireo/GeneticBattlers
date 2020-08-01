#pragma once
#include "SpriteRender.h"
#include "graphics/Skeleton.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Draw();
private:
	SkinModel m_model;		//モデル(ユニティちゃん)
	//SkinModel m_model2;	//モデル２(ユニティちゃん)
	SkinModel m_model3;		//モデル３(地面)
	RenderTarget m_shadowMapRT;		//シャドウマップを描画するレンダリングターゲット
	CVector3 m_ligPos = { 0.0f,300.0f,0.0f };
	CVector3 m_ligDir = { 1.0f,0.0f,0.0f };
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pos2 = { 40.0f,0.0f,0.0f };

	CQuaternion m_rotation = CQuaternion::Identity();			//!<回転。
	Skeleton m_skeleton;		//スケルトン。
	Skeleton m_skeleton2;			//ブレンディング用スケルトン
	Animation m_animation;				//アニメーション。
	Animation m_animation2;				//アニメーションブレンディング用
	AnimationClip m_animClip[1];				//アニメーションクリップ。
	AnimationClip m_animClip2[1];
	std::vector<Bone*> m_bone;
};

