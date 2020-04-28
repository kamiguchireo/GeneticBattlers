#include "stdafx.h"
#include "FontRender.h"

namespace Engine 
{
	namespace prefab 
	{
		bool FontRender::Start()
		{

			return true;
		}

		void FontRender::Update()
		{
			m_font.Begin();
			const wchar_t*text = nullptr;
			if (m_text.c_str() != nullptr)
			{
				text = m_text.c_str();
			}
			m_font.Draw(text,m_position,m_color,m_rotation,m_scale,m_pivot);
			m_font.End();
		}
	}
}