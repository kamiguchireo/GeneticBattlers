#pragma once
class GASceneUI : public IGameObject
{
	typedef std::list<prefab::SpriteRender*> LineList;
public:
	GASceneUI();
	~GASceneUI();
	bool Start();
	void Update();
	/// <summary>
	/// ���݂̐��㐔�Ə������Z�b�g�B
	/// </summary>
	/// <param name="generation">���s����</param>
	/// <param name="maxR">�ő叟��</param>
	/// <param name="aveR">���Ϗ���</param>
	void SetWinRate(const int generation, const int maxR, const float aveR);

	/// <summary>
	/// �ŏI�I�ȏ����B
	/// </summary>
	/// <param name="maxR">�ő叟���B</param>
	/// <param name="aveR">���Ϗ����B</param>
	void EndWinRate(const int maxR, const float aveR);

	//�ŏI���㐔��ݒ�B
	void SetEndGeneration(const int gene)
	{
		m_endGenerationNum = gene;
	}
private:	//�����o�֐��B
	//�X�v���C�g�ǉ��B
	void AddGraphLine();
	//���C����`���B
	void DrawLine(LineList& lineList);

private:		//�萔�B
	const float GRAPH_W = 640.0f;
	const float GRAPH_H = 360.0f;
	float m_wideRange = 0.0f;		//�ꐢ�ゲ�Ƃ̉��̊Ԋu�B
	const float PIXEL_SIZE = 3.0f;
	const CVector2 LINE_PIVOT = { 0.0f,0.5f };

private:
	prefab::SpriteRender* m_sprite = nullptr;			//�w�i�摜�B
	prefab::SpriteRender* m_graph = nullptr;			//�Q�[�W
	prefab::SpriteRender* m_maxWinLine = nullptr;			//�ő叟���X�v���C�g
	prefab::SpriteRender* m_aveWinLine = nullptr;			//���Ϗ����X�v���C�g
	LineList m_maxWinLineList;		//�ő叟���܂���O���t
	LineList m_aveWinLineList;		//���Ϗ����܂���O���t
	prefab::FontRender* m_fontGeneration = nullptr;		//�t�H���g
	prefab::FontRender* m_fontWinRate = nullptr;		//�t�H���g

	int m_currentGenerationNum = 0;		//���㐔�B
	int m_endGenerationNum = 0;			//�ő吢�㐔�B
	int m_maxWinRate = 0;		//�ō���`�q�̏���(%)�B
	float m_aveWinRate = 0.0f;	//���s����̕��Ϗ���(%)�B
	float m_currentProgress = 0.0f;	//���s����̕]���v�Z���B
};

