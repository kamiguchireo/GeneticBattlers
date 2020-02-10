#pragma once
#include <map>
#include <memory>

class CWaveFile;
using CWaveFilePtr = std::shared_ptr<CWaveFile>;
using CWaveFilePtrMap = std::map<unsigned int, CWaveFilePtr>;
//�g�`�f�[�^�o���N
//��x���[�h���ꂽ�g�`�f�[�^���o���N�ɓo�^�ł���
//��x�o�^����΍ēx�ǂݍ��݂��s���K�v���Ȃ��A�o���N����ė��p�ł���
class CWaveFileBank
{
public:
	CWaveFileBank();
	~CWaveFileBank();

	//�O���[�v�P�ʂŉ��
	void Release(int groupID);

	//���ׂĊJ��
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

