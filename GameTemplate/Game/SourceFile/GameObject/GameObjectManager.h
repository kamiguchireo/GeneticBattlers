#pragma once
#include "GameObject.h"
#include "util/Util.h"
#include "SourceFile/graphic/RenderContext.h"

namespace Engine {
	class CGameObjectManager
	{
	public:
		CGameObjectManager()
		{
			m_gameObjectListArray.resize(20);
			m_deleteObjectArray[0].resize(20);
			m_deleteObjectArray[1].resize(20);
		}
		~CGameObjectManager()
		{
		}

	private:
		/*
		ゲームオブジェクトの名前を数字に変換
		*/
		static unsigned int MakeGameObjectNameKey(const char*objectName)
		{
			//デフォルトの名前
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");
			//ハッシュ値
			unsigned int hash;
			//名前がないときデフォルトの名前を入れる
			if (objectName == nullptr)
			{
				hash = defaultNameKey;
			}
			//名前があるときは名前を変換する
			else {
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}

	public:
		//インスタンスの取得
		static CGameObjectManager&Instance()
		{
			static CGameObjectManager instance;
			return instance;
		}
		/*
		ゲームオブジェクトのnew
		newしたら必ずdeleteする
		prio 実行優先順位。
		objectName オブジェクト名
		*/
		template<class T>
		T*NewGameObject(GameObjectPrio prio,const char*objectName)
		{
			(void*)objectName;
			T*newObject = new T();
			m_gameObjectListArray[prio].push_back(newObject);
			unsigned int hash = MakeGameObjectNameKey(objectName);
			newObject->m_isRegist = true;
			newObject->m_priority = prio;
			newObject->m_nameKey = hash;
			newObject->m_isNewFromGameObjectManager = true;
			return newObject;
		}

		/*
		ゲームオブジェクトの検索
		objectName　オブジェクト名
		*/
		template<class T>
		T*FindGameObject(const char*objectName)
		{
			unsigned int nameKey = Util::MakeHash(objectName);
			for (auto goList : m_gameObjectListArray)
			{
				for (auto go : goList)
				{
					if (go->m_nameKey == nameKey)
					{
						//見つけた
						T*p = dynamic_cast<T*>(go);
						return p;
					}
				}
			}
			//見つからなかった
			throw;
			return nullptr;
		}
		/*
		ゲームオブジェクトの検索
		objectName　オブジェクト名
		*/
		template<class T>
		T*FindSpGameObject(const char*objectName)
		{
			unsigned int nameKey = Util::MakeHash(objectName);
			for (auto goList : m_SpgameObjectListArray)
			{
				for (auto go : goList)
				{
					if (go->m_nameKey == nameKey)
					{
						//見つけた
						T*p = dynamic_cast<T*>(go);
						return p;
					}
				}
			}
			//見つからなかった
			throw;
			return nullptr;
		}
		//DeleteGOの名前なしバージョン
		void DeleteGO(IGameObject*go)
		{
			DeleteGameObject(go);
		}
		//DeleteGOの名前ありバージョン
		void DeleteGO(IGameObject*go,const char*objectName)
		{
			//Findして
			go = FindGameObject<IGameObject>(objectName);
			//DeleteGameObjectに入れる
			DeleteGameObject(go);
		}
		//DeleteGOの中身
		void DeleteGameObject(IGameObject*gameObject)
		{
			if (gameObject != nullptr &&gameObject->m_isRegist)
			{
				gameObject->SetDeadMark();
				gameObject->OnDestoroyWrapper();
				gameObject->m_isRegist = false;
				gameObject->m_isRegistDeadList = true;

				m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;
			}
		}

	public:
		void Start();
		void Update();
		void PostRender(RenderContext& rc);
		//描画処理の実行
		void ExecuteRender();
	private:
		//ゲームオブジェクトの削除を実行
		void ExecuteDeleteGameObjects();

		typedef std::list<IGameObject*>GameObjectList;
		std::vector<GameObjectList> m_gameObjectListArray;		//ゲームオブジェクトの優先度付きリスト
		std::vector<GameObjectList> m_deleteObjectArray[2];		//削除するオブジェクトのリスト削除の途中にDeleteGameObjectが呼ばれる可能性が高いので、ダブルバッファ化
		int m_currentDeleteObjectBufferNo = 0;					//現在の削除オブジェクトのバッファ番号
	};

	static inline CGameObjectManager&GameObjectManager()
	{
		return CGameObjectManager::Instance();
	}

	template<class T>
	static inline T*FindGO(const char*objectName)
	{
		return GameObjectManager().FindGameObject<T>(objectName);
	}

	template<class T>
	static inline T*NewGO(int priority,const char*objectName = nullptr, typename T::IGameObject* = nullptr)
	{
		return GameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
	}

	static inline void DeleteGO(IGameObject*go)
	{
		GameObjectManager().DeleteGameObject(go);
	}

	static inline void DeleteGO(const char*objectName)
	{
		IGameObject*go = FindGO<IGameObject>(objectName);
		GameObjectManager().DeleteGameObject(go);
	}

}