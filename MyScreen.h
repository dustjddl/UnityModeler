#pragma once

#include "OglScreen.h"
#include "OglLightMtl.h"
#include "OglSphere.h"
#include "OglCube.h"
#include "OglCylinder.h"
#include "OglTransform.h" 
#include <afxtempl.h> 

class MyScreen :
	public OglScreen
{
public:
	MyScreen(void);

	void AddGameObj(const OglTransform& obj);

protected:
	OglLightMtl m_lightMtl;
	OglSphere m_sphere;
	OglCube m_cube;
	OglCylinder m_cylinder;

	// [수정됨] 두 번째 인자에 const를 붙여야 AddGameObj의 const 참조를 받을 수 있습니다.
	CArray<OglTransform, const OglTransform&> m_arGameObj;

	virtual void InitOpenGL(void);
	virtual void InitRender(void);
	virtual void RenderScene(void);
};