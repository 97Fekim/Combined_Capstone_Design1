// InspectionVoidDlg.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "InspectionVoidDlg.h"
#include "afxdialogex.h"


// CInspectionVoidDlg ��ȭ �����Դϴ�.

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


// CInspectionVoidDlg �޽��� ó�����Դϴ�.


void CInspectionVoidDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


BOOL CInspectionVoidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_sliderthRatio.SetRange(0, 100);
	m_sliderthRatio.SetTicFreq(10);
	m_sliderthRatio.SetPageSize(10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CInspectionVoidDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_sliderthRatio.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_thRatio = m_sliderthRatio.GetPos();
		UpdateData(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CInspectionVoidDlg::OnEnChangeEditthratio()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderthRatio.SetPos(m_thRatio);
}

