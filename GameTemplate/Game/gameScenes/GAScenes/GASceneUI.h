#pragma once
class GASceneUI : public IGameObject
{
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
	void SetWinRate(int generation, int maxR, float aveR);

	/// <summary>
	/// �ŏI�I�ȏ����B
	/// </summary>
	/// <param name="maxR">�ő叟���B</param>
	/// <param name="aveR">���Ϗ����B</param>
	void EndWinRate(int maxR, float aveR);

private:
	prefab::SpriteRender* m_sprite = nullptr;			//�w�i�摜�B
	prefab::SpriteRender* m_gauge = nullptr;			//�Q�[�W
	prefab::SpriteRender* m_meter = nullptr;			//���[�^�[
	prefab::FontRender* m_fontGeneration = nullptr;		//�t�H���g
	prefab::FontRender* m_fontWinRate = nullptr;		//�t�H���g

	int m_currentGenerationNum = 0;		//���㐔�B
	int m_maxWinRate = 0;		//�ō���`�q�̏���(%)�B
	float m_aveWinRate = 0.0f;	//���s����̕��Ϗ���(%)�B
	float m_currentProgress = 0.0f;	//���s����̕]���v�Z���B
};

