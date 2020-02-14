#pragma once
#include "WaveFile.h"
#include "SourceFile/Sound/CWaveFileBank.h"
#include "SourceFile/Sound/CSoundSource.h"



namespace Engine {
	class CWaveFile;
	class CSoundSource;

	class CSoundEngine
	{
	public:
		//コンストラクタ
		CSoundEngine();
		//デストラクタ
		~CSoundEngine();

		//初期化処理
		void Init();

		//解放処理
		void Release();

		//更新処理
		void Update();

		IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile);

		//出力チャンネルの数を取得
		int GetNumChannel()const
		{
			return m_nChannels;
		}

		//波形データバンクを取得
		CWaveFileBank&GetWaveFileBank()
		{
			return m_waveFileBank;
		}

		auto RemoveSoundSource(prefab::CSoundSource* ss)
		{
			auto it = std::find(m_soundSources.begin(), m_soundSources.end(), ss);
			if (it != m_soundSources.end()) {
				it = m_soundSources.erase(it);
			}
			return it;

		}

	private:
		IXAudio2* m_xAudio2 = nullptr;
		IXAudio2MasteringVoice* m_masteringVoice = nullptr;
		IUnknown* m_reverbEffect = nullptr;
		IXAudio2SubmixVoice* m_submixVoice = nullptr;
		CWaveFileBank m_waveFileBank;		//波形データのバンク
		DWORD m_channelMask = 0;
		DWORD m_nChannels = 0;
		bool m_isInited = false;
		std::list<prefab::CSoundSource*> m_soundSources;
	};
}

//サウンドエンジンのインスタンス。
extern CSoundEngine* m_soundEngine;