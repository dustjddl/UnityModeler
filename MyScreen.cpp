#include "pch.h"
#include "MyScreen.h"
#include "OglTransform.h"

MyScreen::MyScreen(void)
{
	SetBackColor(RGB(0, 0, 255)); // 기본 배경색: 파란색
}

// [추가] 외부(Dialog)에서 게임 오브젝트를 받아와 배열에 추가하는 함수
void MyScreen::AddGameObj(const OglTransform& obj)
{
	m_arGameObj.Add(obj); // 멤버 변수 배열에 오브젝트 저장
	Invalidate(FALSE);    // 화면 갱신 요청 (WM_PAINT 메시지 발생 -> RenderScene 호출됨)
}

void MyScreen::InitOpenGL(void)
{
	OglScreen::InitOpenGL();

	StartRC();

	m_lightMtl.SetLightParam(); // 조명 설정
	m_sphere.Create();          // 구(Sphere) 그리기 도구 초기화 (Quadric 생성)
	m_cylinder.Create();        // 원기둥(Cylinder) 그리기 도구 초기화
	SetViewport();

	StopRC();
}

void MyScreen::InitRender(void)
{
	OglScreen::InitRender();
}

void MyScreen::RenderScene(void)
{
	OglScreen::RenderScene(); // 기본 화면(배경색 등) 지우기

	// [수정] 사용자가 추가한 모든 게임 오브젝트를 순회하며 그리기
	for (int i = 0; i < m_arGameObj.GetCount(); i++)
	{
		OglTransform elt = m_arGameObj[i]; // i번째 오브젝트 정보 가져오기

		// 오브젝트 타입에 맞춰 그리기 함수 호출
		switch (elt.m_nType)
		{
		case GameObjType::SPHERE:
			m_sphere.Draw(elt);
			break;
		case GameObjType::CUBE:
			m_cube.Draw(elt);
			break;
		case GameObjType::CYLINDER:
			m_cylinder.Draw(elt);
			break;
			// 추후 다른 타입(Quad, Plane 등)이 추가되면 여기에 case를 추가하면 됩니다.
		}
	}
}