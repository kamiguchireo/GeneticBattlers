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
		//�C�x���g
		enum EnEvent {
			enEvent_Undef,		//����`�C�x���g
			enEvent_Destroy		//�C���X�^���X���j�������
		};

		//�C�x���g�������̃f�[�^
		struct SEventParam {
			EnEvent eEvent = enEvent_Undef;		//�������Ă���C�x���g
			IGameObject*gameObject = nullptr;	//�C�x���g��ʒm���Ă���Q�[���I�u�W�F�N�g�̃C���X�^���X
		};
	public:
	//������
	virtual bool Start() { return true; }
	//�X�V
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
					//���������������B
					m_isStart = true;
				}
			}
		}
		void OnDestoroyWrapper()
		{
			SEventParam param;
			param.eEvent = enEvent_Destroy;
			param.gameObject = this;
			//�f�X�g���C�C�x���g�����X�i�[�ɒʒm����B
			for (auto&listener : m_eventListeners)
			{
				listener(param);
			}
		}

		//Render�֐������s���ꂽ��ŌĂ΂��`�揈��
		virtual void PostRender(RenderContext& renderContext)
		{
			(void)renderContext;
		}

		void SetDeadMark()
		{
			m_isDead = true;
		}
		//���S����B
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
		GameObjectPrio	m_priority;			//!<���s�D��x�B
		bool m_isStart;						//�X�^�[�g�֐����I��������ǂ���
		unsigned int m_nameKey = 0;			//!<���O�L�[�B
		bool m_isRegistDeadList = false;	//!<���S���X�g�ɐς܂�Ă���B
		bool m_isNewFromGameObjectManager;	//!<GameObjectManager��new���ꂽ
		bool m_isRegist = false;			//!<GameObjectManager�ɓo�^����Ă��邩�ǂ���
		bool m_isDead;						//!<���S�t���O�B
		bool m_isActive = true;				//Active�t���O
		std::list<std::function<void(SEventParam&eventParam)>> m_eventListeners;	//�C�x���g���X�i�[
	
	};
}