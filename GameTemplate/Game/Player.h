#pragma once
#include "stdafx.h"
#include "character/CharacterController.h"
#include "GameObjectManager.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標。
};

