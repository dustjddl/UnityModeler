#pragma once
#include "afxdialogex.h"

// CDlgGameObj 대화 상자

class CDlgGameObj : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGameObj)

public:
	CDlgGameObj(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgGameObj();

	// 리스트 박스 포인터 설정 함수
	void SetLbGameObj(CListBox* ptr) { m_pLbGameObj = ptr; }

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOBJ };
#endif

protected:
	CListBox* m_pLbGameObj; // 게임 오브젝트 이름 목록을 관리할 리스트 박스 포인터
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	// --- UI 컨트롤과 연결될 멤버 변수들 ---

	// 1. 기본 속성
	CString m_sName;            // 이름 (IDC_EDIT_NAME)
	CComboBox m_comboType;      // 타입 콤보박스 (IDC_COMBO_TYPE)
	CMFCColorButton m_btnColor; // 색상 버튼 (IDC_MFCCOLORBUTTON1)
	float m_fAlpha;             // 투명도 (IDC_EDIT_ALPHA)

	// 2. Transform - Position (IDC_EDIT_POS_X/Y/Z)
	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;

	// 3. Transform - Rotation (IDC_EDIT_ROT_X/Y/Z)
	float m_fRotX;
	float m_fRotY;
	float m_fRotZ;

	// 4. Transform - Scale (IDC_EDIT_SCALE_X/Y/Z)
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;

	// --- 이벤트 핸들러 함수 ---

	// Add Game Object 버튼 클릭 시 호출
	afx_msg void OnBnClickedButtonAdd();
};