#pragma once
#include <random>

class CRandom
{
public:
	CRandom();
	~CRandom();

	//�����Ȃ������^
	unsigned int GetRandomInt()
	{
		return mt();
	}

	double GetRandomDouble()
	{
		return static_cast<double>(GetRandomInt())*(1.0 / 4294967295.0);
	}

private:
	//std::random_device rnd;     // �񌈒�I�ȗ���������
	std::mt19937 mt;     // �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
};

extern CRandom g_random;
