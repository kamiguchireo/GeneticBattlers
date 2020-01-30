#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	if (!m_sprite)
	{
		DeleteGO(m_sprite);
	}
}

bool TitleScene::Start()
{
	return true;
}

void TitleScene::Update()
{
}
