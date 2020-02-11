#pragma once
#include "WaveFile.h"

//�����N���X
//�I���������ɏ悹��ꍇ��CSoundSource::Init���g���ď��������s���Ă�������
//�X�g���[�~���O�Đ����s���ꍇ��CSoundSource::InitStreaming���g�p���Ă�������
namespace Engine {
	namespace prefab {
		class CSoundSource:public IGameObject
		{
		public:
			CSoundSource();
			~CSoundSource();

			//�������
			void Release();

			//������
			//�I���������Đ������̏�����
			//filePath		�t�@�C���p�X
			//is3DSound		3D�T�E���h���ǂ���
			void Init(wchar_t*filePath);

			//�X�g���[�~���O�Đ������̏�����
			void InitStreaming(wchar_t* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
			
			//�Đ�
			//isLoop		���[�v�Đ��t���O
			void Play(bool isLoop);

			//�X�V
			void Update();

			bool IsPlaying()
			{
				return m_isPlaying;
			}
		private:
			//�X�g���[�~���O�Đ����̍X�V�����B
			void UpdateStreaming();
			//�I���������Đ����̍X�V�����B
			void UpdateOnMemory();
			void Play(char* buff, unsigned int bufferSize);
			void StartStreamingBuffring();

		private:
			enum EnStreamingStatus {
				enStreamingBuffering,	//�o�b�t�@�����O���B
				enStreamingQueueing,	//�L���[�C���O���B
			};

			std::shared_ptr<CWaveFile> m_waveFile;
			FLOAT32 m_emitterAzimuths[2];
			FLOAT32 m_matrixCoefficients[2 * 8];
			bool m_isStreaming = false;		//�X�g���[�~���O�Đ����ǂ���
			IXAudio2SourceVoice* m_sourceVoice = nullptr;		//�\�[�X�{�C�X
			bool m_is3DSound = false;		//3D�T�E���h���ǂ���
			X3DAUDIO_DSP_SETTINGS m_dspSettings;
			bool m_isAvailable = false;			//�C���X�^���X�����p�\���ǂ���
			unsigned int			m_streamingBufferSize = 0;	//!<�X�g���[�~���O�p�̃o�b�t�@�����O�T�C�Y�B
			unsigned int			m_currentBufferingSize = 0;	//!<���݂̃o�b�t�@�����O�̃T�C�Y�B
			unsigned int			m_readStartPos = 0;			//!<�ǂݍ��݊J�n�ʒu�B
			unsigned int			m_ringBufferSize = 0;		//!<�����O�o�b�t�@�̃T�C�Y�B
			EnStreamingStatus		m_streamingState = enStreamingBuffering;	//!<�X�g���[�~���O�X�e�[�^�X�B
			bool						m_isPlaying = false;		//!<�Đ����t���O�B
			bool						m_isLoop = false;			//!<���[�v�t���O�B

		};
	}
}