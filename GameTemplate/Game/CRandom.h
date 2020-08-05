#pragma once
#include <random>

class CRandom
{
public:
	CRandom();
	~CRandom();

	//符号なし整数型
	unsigned int GetRandomInt()
	{
		return mt();
	}

	double GetRandomDouble()
	{
		return static_cast<double>(GetRandomInt())*(1.0 / 4294967295.0);
	}

private:
	//std::random_device rnd;     // 非決定的な乱数生成器
	std::mt19937 mt;     // メルセンヌ・ツイスタの32ビット版、引数は初期シード
};

extern CRandom g_random;
