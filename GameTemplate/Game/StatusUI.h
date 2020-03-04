#pragma once
class StatusUI:public IGameObject
{
public:
	StatusUI();
	~StatusUI();
	bool Start();
	void Update();

	//UI�̍��W��ݒ肷��B
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	//�Q�[�W�̑傫����ݒ�B
	void SetScaling(float scale) {
		m_scaleX = scale;
	}
	//HP�Q�[�W�̑傫����ݒ�B
	void SetHPScaling(float scale) {
		m_hpX = scale;
		m_HPG->SetScale({ m_hpX,1.0f,1.0f });
	}

private:
	prefab::SpriteRender* m_para = nullptr;		//!<�p�����[�^�w�i
	prefab::SpriteRender* m_ATB = nullptr;		//!<ATB�o�[
	prefab::SpriteRender* m_ATBG = nullptr;		//!<ATB�Q�[�W
	prefab::SpriteRender* m_HP = nullptr;		//!<HP�o�[
	prefab::SpriteRender* m_HPG = nullptr;		//!<HP�Q�[�W

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	//pivot		�N�_
	//0.5, 0.5�ŉ摜�̒��S���N�_�B
	//0.0, 0.0�ŉ摜�̍����B
	//1.0, 1.0�ŉ摜�̉E��B
	CVector2 m_pivot = CVector2::Zero();
	float m_scaleX = 0.0f;
	float m_hpX = 1.0f;

};

