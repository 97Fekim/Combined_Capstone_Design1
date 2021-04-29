// InspectionVoidDlg.cpp : 구현 파일입니다.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "InspectionVoidDlg.h"
#include "afxdialogex.h"


// CInspectionVoidDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInspectionVoidDlg, CDialogEx)

CInspectionVoidDlg::CInspectionVoidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSPECTION_VOID, pParent)
	, m_thRatio(0)
{

}

CInspectionVoidDlg::~CInspectionVoidDlg()
{
}

void CInspectionVoidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDV_MinMaxInt(pDX, m_thRatio, 0, 100);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderthRatio);
	DDX_Text(pDX, IDC_EDIT_thRatio, m_thRatio);
	
}


BEGIN_MESSAGE_MAP(CInspectionVoidDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CInspectionVoidDlg::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_thRatio, &CInspectionVoidDlg::OnEnChangeEditthratio)
END_MESSAGE_MAP()


// CInspectionVoidDlg 메시지 처리기입니다.


void CInspectionVoidDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


BOOL CInspectionVoidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_sliderthRatio.SetRange(0, 100);
	m_sliderthRatio.SetTicFreq(10);
	m_sliderthRatio.SetPageSize(10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CInspectionVoidDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderthRatio.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_thRatio = m_sliderthRatio.GetPos();
		UpdateData(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CInspectionVoidDlg::OnEnChangeEditthratio()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderthRatio.SetPos(m_thRatio);
}

