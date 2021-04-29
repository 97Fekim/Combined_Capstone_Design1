// MedianBlur.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "MedianBlur.h"
#include "afxdialogex.h"


// CMedianBlur 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMedianBlur, CDialogEx)

CMedianBlur::CMedianBlur(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEDIAN_BLUR, pParent)
	, m_maskSize(0)
{

}

CMedianBlur::~CMedianBlur()
{
}

void CMedianBlur::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_maskSize);
	DDV_MinMaxInt(pDX, m_maskSize, 3, 30);
}


BEGIN_MESSAGE_MAP(CMedianBlur, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &CMedianBlur::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CMedianBlur 메시지 처리기입니다.


BOOL CMedianBlur::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMedianBlur::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}
