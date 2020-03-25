#include "stdafx.h"
#include "GameObjectManager.h"

namespace Engine {

	void CGameObjectManager::Start()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->StartWrapper();
			}
		}
	}

	void CGameObjectManager::Update()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->UpdateWrapper();
			}
		}
		//ExecuteRender();
		ExecuteDeleteGameObjects();
	}

	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//�o�b�t�@��؂�ւ�
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for (GameObjectList&goList : m_deleteObjectArray[preBufferNo])
		{
			for (IGameObject*go : goList)
			{
				GameObjectPrio prio = go->GetPriority();
				GameObjectList&goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end())
				{
					//�폜���X�g���珜�O�B
					(*it)->m_isRegistDeadList = false;
					if ((*it)->IsNewFromGameObjectManagr())
					{
						delete(*it);
					}

				}
				goExecList.erase(it);
			}
			goList.clear();
		}
	}

	void CGameObjectManager::PostRender(RenderContext& rc)
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->PostRenderWrapper(rc);
			}
		}
	}

	void CGameObjectManager::ExecuteRender()
	{
		RenderContext& renderContext = g_graphicsEngine->GetRenderContext();
		//2D�̕\��
		//g_graphicsEngine->Execute2DDraw();
		PostRender(renderContext);
	}
}