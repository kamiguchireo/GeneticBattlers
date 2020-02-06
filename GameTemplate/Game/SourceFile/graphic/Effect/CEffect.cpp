#include "stdafx.h"
#include "CEffect.h"

namespace Engine {
	namespace prefab {
		CEffect::CEffect()
		{
		}
		CEffect::~CEffect()
		{
			Release();
		}

		void CEffect::Release()
		{
			if (m_handle != -1)
			{
			}
		}
	}
}