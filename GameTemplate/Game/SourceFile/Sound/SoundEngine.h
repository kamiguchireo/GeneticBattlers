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
		//�R���X�g���N�^
		CSoundEngine();
		//�f�X�g���N�^
		~CSoundEngine();

		//����������
		void Init();

		//�������
		void Release();

		//�X�V����
		void Update();

		IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile);

		//3D�T�E���h�\�[�X���폜
		void Remove3DSoundSource(prefab::CSoundSource*ss)
		{
			auto it = std::find(m_soundSources.begin(), m_soundSources.end(), ss);
			if (it != m_soundSources.end())
			{
				m_soundSources.erase(it);
			}
		}

		//�o�̓`�����l���̐����擾
		int GetNumChannel()const
		{
			return m_nChannels;
		}

		//�g�`�f�[�^�o���N���擾
		CWaveFileBank&GetWaveFileBank()
		{
			return m_waveFileBank;
		}

		//3D�T�E���h�\�[�X��ǉ�
		void Add3DSoundSource(prefab::CSoundSource*ss)
		{
			m_soundSources.push_back(ss);
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
		CWaveFileBank m_waveFileBank;		//�g�`�f�[�^�̃o���N
		DWORD m_channelMask = 0;
		DWORD m_nChannels = 0;
		bool m_isInited = false;
		std::list<prefab::CSoundSource*> m_soundSources;
	};
}

//�T�E���h�G���W���̃C���X�^���X�B
extern CSoundEngine* m_soundEngine;