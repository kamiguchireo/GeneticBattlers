#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。
Camera g_camera2D;

void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	{
		//プロジェクション行列を計算。
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//画角。
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
			m_near,
			m_far
		);
	}
}

void Camera::Update2D()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	m_projMatrix.MakeOrthoProjectionMatrix(FRAME_BUFFER_W, FRAME_BUFFER_H, m_near, m_far);

}