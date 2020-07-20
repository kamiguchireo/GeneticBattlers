#pragma once
#include "SourceFile/graphic/RenderContext.h"
#include "SourceFile/Noncopyable.h"

namespace Engine {
	typedef unsigned char	GameObjectPrio;

	class IGameObject:Engine::Noncopyable
	{
	public:
		IGameObject():
			m_priority(0),
			m_isStart(false),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		virtual	~IGameObject()
		{
		}
	
	public:
		//イベント
		enum EnEvent {
			enEvent_Undef,		//未定義イベント
			enEvent_Destroy		//インスタンスが破棄される
		};

		//イベント発生時のデータ
		struct SEventParam {
			EnEvent eEvent = enEvent_Undef;		//発生しているイベント
			IGameObject*gameObject = nullptr;	//イベントを通知しているゲームオブジェクトのインスタンス
		};
	public:
	//初期化
	virtual bool Start() { return true; }
	//更新
	virtual void Update() {}
	
	public:
		void PostRenderWrapper(RenderContext& renderContext)
		{
			if (m_isActive&&m_isStart && !m_isDead && !m_isRegistDeadList)
			{
				PostRender(renderContext);
			}
		}

	public:
		void UpdateWrapper()
		{
			if (m_isStart == true && m_isDead == false)
			{
				Update();
			}
		}
		void StartWrapper()
		{
			if (m_isStart == false) {
				if (Start()) {
					//初期化処理完了。
					m_isStart = true;
				}
			}
		}
		void OnDestoroyWrapper()
		{
			SEventParam param;
			param.eEvent = enEvent_Destroy;
			param.gameObject = this;
			//デストロイイベントをリスナーに通知する。
			for (auto&listener : m_eventListeners)
			{
				listener(param);
			}
		}

		//Render関数が実行された後で呼ばれる描画処理
		virtual void PostRender(RenderContext& renderContext)
		{
			(void)renderContext;
		}

		void SetDeadMark()
		{
			m_isDead = true;
		}
		//死亡判定。
		bool IsDead()const
		{
			return m_isDead;
		}

		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}

		bool IsNewFromGameObjectManagr() const
		{
			return m_isNewFromGameObjectManager;
		}
		friend class CGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<実行優先度。
		bool m_isStart;						//スタート関数が終わったかどうか
		unsigned int m_nameKey = 0;			//!<名前キー。
		bool m_isRegistDeadList = false;	//!<死亡リストに積まれている。
		bool m_isNewFromGameObjectManager;	//!<GameObjectManagerでnewされた
		bool m_isRegist = false;			//!<GameObjectManagerに登録されているかどうか
		bool m_isDead;						//!<死亡フラグ。
		bool m_isActive = true;				//Activeフラグ
		std::list<std::function<void(SEventParam&eventParam)>> m_eventListeners;	//イベントリスナー
	
	};
}