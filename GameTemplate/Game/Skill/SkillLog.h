#pragma once
class SkillLog:public IGameObject
{
public:
	SkillLog();
	~SkillLog();
	bool Start();
	void Update();
	void SetText(const wchar_t* text)
	{
		m_skillText = text;
	}

	static SkillLog* GetInstance()
	{
		return m_instance;
	}
	/// <summary>
	/// MP������Ă��邩�H����Ă��Ȃ��Ȃ�true���Z�b�g�B
	/// </summary>
	/// <param name="flag">�t���O����Ă��Ȃ��Ȃ�true�ɂ��Ă����Ƃ����B</param>
	void SetMPShortage(bool flag)
	{
		m_isMP = flag;
	}
	//���Ԍo�ߍ폜�t���O�ݒ�B
	void SetDelete(bool flag)
	{
		m_countDown = flag;
	}
private:
	void CreateMPLog();

private:	//�萔�B
	static const CVector2 SLOG_POSITION;
	static const CVector2 MPLOG_POSITION;
	static const CVector2 WINDOW_SIZE;

private:
	static SkillLog* m_instance;
	prefab::SpriteRender* m_sprite = nullptr;	//�E�B���h�E�̃X�v���C�g�B
	prefab::SpriteRender* m_mpSprite = nullptr;	//�uMP������Ȃ��v��\������E�B���h�E�̃X�v���C�g�B
	prefab::FontRender* m_font = nullptr;		//�\������t�H���g�B
	prefab::FontRender* m_mpLog = nullptr;		//�uMP������Ȃ��v��\������B
	
	const wchar_t* m_skillText = nullptr;		//�X�L�����B

	float m_deleteTime = 0.65f;		//�폜�܂ł̎��ԁB(�b)

	bool m_isMP = false;			//MP�����Ȃ����H
	bool m_countDown = false;		//���Ԍo�ߌ�폜�t���O�B
};

