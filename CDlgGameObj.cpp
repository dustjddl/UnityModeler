// CDlgGameObj.cpp: 구현 파일
//

#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgGameObj.h"
// [중요] 메인 다이얼로그와 Screen에 접근하기 위해 헤더 포함
#include "UnityModelerDlg.h" 
#include "OglTransform.h"


// CDlgGameObj 대화 상자

IMPLEMENT_DYNAMIC(CDlgGameObj, CDialogEx)

CDlgGameObj::CDlgGameObj(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEOBJ, pParent)
	, m_sName(_T("GameObject")) // 기본 이름
	, m_fAlpha(1.0f)            // 기본 투명도: 불투명
	, m_fPosX(0.f), m_fPosY(0.f), m_fPosZ(0.f)
	, m_fRotX(0.f), m_fRotY(0.f), m_fRotZ(0.f)
	, m_fScaleX(1.f), m_fScaleY(1.f), m_fScaleZ(1.f) // [중요] 스케일은 1로 초기화 (0이면 안 보임)
{
	m_pLbGameObj = nullptr;
}

CDlgGameObj::~CDlgGameObj()
{
}

void CDlgGameObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// 1. 이름 및 타입
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);

	// 2. 색상 및 투명도
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_btnColor);
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_fAlpha);

	// 3. Transform - Position
	DDX_Text(pDX, IDC_EDIT_POS_X, m_fPosX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_fPosY);
	DDX_Text(pDX, IDC_EDIT_POS_Z, m_fPosZ);

	// 4. Transform - Rotation
	DDX_Text(pDX, IDC_EDIT_ROT_X, m_fRotX);
	DDX_Text(pDX, IDC_EDIT_ROT_Y, m_fRotY);
	DDX_Text(pDX, IDC_EDIT_ROT_Z, m_fRotZ);

	// 5. Transform - Scale
	DDX_Text(pDX, IDC_EDIT_SCALE_X, m_fScaleX);
	DDX_Text(pDX, IDC_EDIT_SCALE_Y, m_fScaleY);
	DDX_Text(pDX, IDC_EDIT_SCALE_Z, m_fScaleZ);
}


BEGIN_MESSAGE_MAP(CDlgGameObj, CDialogEx)
	// [수정] Add 버튼 클릭 이벤트 매핑
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgGameObj::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CDlgGameObj 메시지 처리기

// Add Game Object 버튼 클릭 시 호출
void CDlgGameObj::OnBnClickedButtonAdd()
{
	// 1. UI의 값을 변수로 가져오기
	if (!UpdateData(TRUE)) return;

	// 2. 데이터를 담을 OglTransform 객체 생성
	OglTransform ot;

	// 2-1. 타입 설정
	// 콤보박스 선택 인덱스: 0, 1, 2... -> Enum: 1(SPHERE), 2(CUBE)... 로 매핑
	int nSel = m_comboType.GetCurSel();
	if (nSel == -1)
	{
		AfxMessageBox(_T("오브젝트 타입을 선택해주세요."));
		return;
	}
	ot.m_nType = (GameObjType)(nSel + 1);

	// 2-2. 색상 및 투명도 설정
	ot.m_nColor = m_btnColor.GetColor(); // CMFCColorButton에서 현재 색상 가져오기
	ot.m_alpha = m_fAlpha;

	// 2-3. Transform 설정
	ot.m_translate = Vector3(m_fPosX, m_fPosY, m_fPosZ);
	ot.m_rotate = Vector3(m_fRotX, m_fRotY, m_fRotZ);
	ot.m_scale = Vector3(m_fScaleX, m_fScaleY, m_fScaleZ);

	// 3. 메인 다이얼로그를 통해 MyScreen에 객체 추가
	CUnityModelerDlg* pMainDlg = dynamic_cast<CUnityModelerDlg*>(AfxGetMainWnd());
	if (pMainDlg)
	{
		// 메인 다이얼로그 -> Screen 객체 얻기 -> 오브젝트 추가 함수 호출
		pMainDlg->GetScreen()->AddGameObj(ot);

		// 4. (선택사항) 리스트 박스에 추가된 오브젝트 이름 등록
		if (m_pLbGameObj)
		{
			m_pLbGameObj->AddString(m_sName);
		}
	}
}