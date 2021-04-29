// ErodeDlg.cpp : 구현 파일입니다.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "ErodeDlg.h"
#include "afxdialogex.h"


// CErodeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CErodeDlg, CDialogEx)

CErodeDlg::CErodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ERODE, pParent)
	, m(0)
{

}

CErodeDlg::~CErodeDlg()
{
}

void CErodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ERODE, m);
	DDV_MinMaxInt(pDX, m, 3, 30);
}


BEGIN_MESSAGE_MAP(CErodeDlg, CDialogEx)
	ON_EN_CHANGE(IDC_ERODE, &CErodeDlg::OnEnChangeErode)
END_MESSAGE_MAP()


// CErodeDlg 메시지 처리기입니다.


BOOL CErodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CErodeDlg::OnEnChangeErode()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}
