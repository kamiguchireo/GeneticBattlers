#pragma once
class StatusUI:public IGameObject
{
public:
	StatusUI();
	~StatusUI();
	bool Start();
	void Update();

	//UIの座標を設定する。
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	//敵用UIにする。
	void EnableEnemy() {
		m_isEnemy = true;
	}
	//ゲージの大きさを設定。
	void SetScaling(float scale) {
		m_scaleX = scale;
	}
	//HPゲージの大きさを設定。
	void SetHPScaling(float scale) {
		m_hpX = scale;
		m_HPG->SetScale({ m_hpX,1.0f,1.0f });
	}
	//評価ボタンの選択。
	void SetGood() {
		m_Good->SetMulColor(m_White);
		m_Bad->SetMulColor(m_Gray);
	}
	void SetBad() {
		m_Good->SetMulColor(m_Gray);
		m_Bad->SetMulColor(m_White);
	}
	void ScoreReset(){
		m_Good->SetMulColor(m_Gray);
		m_Bad->SetMulColor(m_Gray);
	}

private:
	prefab::SpriteRender* m_para = nullptr;		//!<パラメータ背景
	prefab::SpriteRender* m_ATB = nullptr;		//!<ATBバー
	prefab::SpriteRender* m_ATBG = nullptr;		//!<ATBゲージ
	prefab::SpriteRender* m_HP = nullptr;		//!<HPバー
	prefab::SpriteRender* m_HPG = nullptr;		//!<HPゲージ
	prefab::SpriteRender* m_Good = nullptr;		//!<Goodボタン
	prefab::SpriteRender* m_Bad = nullptr;		//!<Badボタン

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	//pivot		起点
	//0.5, 0.5で画像の中心が起点。
	//0.0, 0.0で画像の左下。
	//1.0, 1.0で画像の右上。
	CVector2 m_pivot = CVector2::Zero();
	const static CVector3 m_Gray;			//グレー。
	const static CVector3 m_White;			//ホワイト。
	float m_scaleX = 0.0f;
	float m_hpX = 1.0f;
	bool m_isEnemy = false;
};

