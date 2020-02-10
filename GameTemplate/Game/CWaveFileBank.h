#pragma once
#include <map>
#include <memory>

class CWaveFile;
using CWaveFilePtr = std::shared_ptr<CWaveFile>;
using CWaveFilePtrMap = std::map<unsigned int, CWaveFilePtr>;
//波形データバンク
//一度ロードされた波形データをバンクに登録できる
//一度登録すれば再度読み込みを行う必要がなく、バンクから再利用できる
class CWaveFileBank
{
public:
	CWaveFileBank();
	~CWaveFileBank();

	//グループ単位で解放
	void Release(int groupID);

	//すべて開放
	void ReleaseAll()
	{
		for (int i = 0; i < MAX_GROUP; i++)
		{
			Release(i);
		}
	}

private:
	static const int MAX_GROUP = 256;
};

