// FastInspectionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FastInspectionDlg.h"
#include "afxdialogex.h"


// CFastInspectionDlg ��ȭ �����Դϴ�.

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


// CFastInspectionDlg �޽��� ó�����Դϴ�.


BOOL CFastInspectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_sliderRatio.SetRange(0, 100);
	m_sliderRatio.SetTicFreq(10);
	m_sliderRatio.SetPageSize(10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CFastInspectionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_sliderRatio.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_Ratio = m_sliderRatio.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CFastInspectionDlg::OnEnChangeEditthratio()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderRatio.SetPos(m_Ratio);
}
