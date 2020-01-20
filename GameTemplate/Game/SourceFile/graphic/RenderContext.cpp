#include "stdafx.h"
#include "RenderContext.h"

namespace Engine {
	void RenderContext::Init(ID3D11DeviceContext*pD3DDeviceContext, ID3D11DeviceContext*pD3DDeferredDeviceContext)
	{
		m_pD3DImmidiateDeviceContext = pD3DDeviceContext;
		if (pD3DDeferredDeviceContext != nullptr)
		{
			m_pD3DDeviceContext = pD3DDeferredDeviceContext;
		}
		else
		{
			m_pD3DDeviceContext = m_pD3DImmidiateDeviceContext;
		}
	}
}