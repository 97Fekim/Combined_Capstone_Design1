// FastInspectionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FastInspectionDlg.h"
#include "afxdialogex.h"


// CFastInspectionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFastInspectionDlg, CDialogEx)

CFastInspectionDlg::CFastInspectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FAST_INSPECT, pParent)
	, m_Ratio(0)
{

}

CFastInspectionDlg::~CFastInspectionDlg()
{
}

void CFastInspectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RATIO_SLIDER, m_sliderRatio);
	DDX_Text(pDX, IDC_RATIO_EDIT, m_Ratio);
	DDV_MinMaxInt(pDX, m_Ratio, 0, 100);
}


BEGIN_MESSAGE_MAP(CFastInspectionDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_thRatio, &CFastInspectionDlg::OnEnChangeEditthratio)
END_MESSAGE_MAP()


// CFastInspectionDlg 메시지 처리기입니다.


BOOL CFastInspectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_sliderRatio.SetRange(0, 100);
	m_sliderRatio.SetTicFreq(10);
	m_sliderRatio.SetPageSize(10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFastInspectionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderRatio.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_Ratio = m_sliderRatio.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CFastInspectionDlg::OnEnChangeEditthratio()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderRatio.SetPos(m_Ratio);
}
