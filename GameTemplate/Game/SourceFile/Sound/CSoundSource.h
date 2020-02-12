#pragma once
#include "WaveFile.h"

//音源クラス
//オンメモリに乗せる場合はCSoundSource::Initを使って初期化を行ってください
//ストリーミング再生を行う場合はCSoundSource::InitStreamingを使用してください
namespace Engine {
	namespace prefab {
		class CSoundSource:public IGameObject
		{
		public:
			CSoundSource();
			~CSoundSource();

			//解放処理
			void Release();

			//初期化
			//オンメモリ再生向けの初期化
			//filePath		ファイルパス
			//is3DSound		3Dサウンドかどうか
			void Init(wchar_t*filePath);

			//ストリーミング再生向けの初期化
			void InitStreaming(wchar_t* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
			
			//再生
			//isLoop		ループ再生フラグ
			void Play(bool isLoop);

			//更新
			void Update();

			bool IsPlaying()
			{
				return m_isPlaying;
			}
		private:
			//ストリーミング再生中の更新処理。
			void UpdateStreaming();
			//オンメモリ再生中の更新処理。
			void UpdateOnMemory();
			void Play(char* buff, unsigned int bufferSize);
			void StartStreamingBuffring();

		private:
			enum EnStreamingStatus {
				enStreamingBuffering,	//バッファリング中。
				enStreamingQueueing,	//キューイング中。
			};

			std::shared_ptr<CWaveFile> m_waveFile;
			FLOAT32 m_emitterAzimuths[2];
			FLOAT32 m_matrixCoefficients[2 * 8];
			bool m_isStreaming = false;		//ストリーミング再生かどうか
			IXAudio2SourceVoice* m_sourceVoice = nullptr;		//ソースボイス
			bool m_is3DSound = false;		//3Dサウンドかどうか
			X3DAUDIO_DSP_SETTINGS m_dspSettings;
			bool m_isAvailable = false;			//インスタンスが利用可能かどうか
			unsigned int			m_streamingBufferSize = 0;	//!<ストリーミング用のバッファリングサイズ。
			unsigned int			m_currentBufferingSize = 0;	//!<現在のバッファリングのサイズ。
			unsigned int			m_readStartPos = 0;			//!<読み込み開始位置。
			unsigned int			m_ringBufferSize = 0;		//!<リングバッファのサイズ。
			EnStreamingStatus		m_streamingState = enStreamingBuffering;	//!<ストリーミングステータス。
			bool						m_isPlaying = false;		//!<再生中フラグ。
			bool						m_isLoop = false;			//!<ループフラグ。

		};
	}
}