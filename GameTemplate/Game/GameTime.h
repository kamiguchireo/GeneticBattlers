#pragma once
#include "StopWatch.h"
#include <list>

class GameTime
{
public:
	GameTime() {}
	~GameTime() {}
	//1�t���[���̌o�ߎ��Ԃ��擾
	const float GetFrameDeltaTime()const
	{
		return m_frameDeltaTime;
	}

	void PushFrameDeltaTime(float deltaTime)
	{
		m_frameDeltaTimeQue.push_back(deltaTime);
		if (m_frameDeltaTimeQue.size() > 5)
		{
			float totalTime = 0.0f;
			for (auto time : m_frameDeltaTimeQue)
			{
				totalTime += time;
			}
			//���ϒl���Ƃ�
			m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
			//�擪�v�f���폜
			m_frameDeltaTimeQue.pop_front();
		}
	}

	float GetFPS()
	{
		return 1.0f / m_frameDeltaTime;
	}

	//fps�̍ő�l���Œ�
	void SetMaxFPS(int maxFPS)
	{
		int SleepFrame = static_cast<int>(1.0f / m_frameDeltaTime) - maxFPS;
		SleepFrame = max(SleepFrame, 0);
		Sleep(SleepFrame);
	}
private:
	std::list<float> m_frameDeltaTimeQue;
	float		m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB
};

extern GameTime g_gameTime;