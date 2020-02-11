#include "stdafx.h"
#include "WaveFile.h"
#include "CWaveFileBank.h"
#include "util/Util.h"

namespace Engine {
	CWaveFileBank::CWaveFileBank()
	{
	}
	CWaveFileBank::~CWaveFileBank()
	{
		ReleaseAll();
	}
	void CWaveFileBank::Release(int groupID)
	{
		for (auto waveFile : m_waveFileMap[groupID]) {
			waveFile.second->Release();
		}
		m_waveFileMap[groupID].clear();
	}
	void CWaveFileBank::UnregistWaveFile(int groupID, CWaveFilePtr waveFile)
	{
		m_waveFileMap->erase(waveFile->GetFilePathHash());
	}
	void CWaveFileBank::RegistWaveFile(int groupID, CWaveFilePtr waveFile)
	{
		m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
	}
	CWaveFilePtr CWaveFileBank::FindWaveFile(int groupID, const wchar_t* filePath)
	{
		auto value = m_waveFileMap[groupID].find(Util::MakeHash(filePath));
		if (value != m_waveFileMap[groupID].end()) {
			return value->second;
		}
		return CWaveFilePtr();
	}
}