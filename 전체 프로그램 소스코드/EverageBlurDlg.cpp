// EverageBlurDlg.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "EverageBlurDlg.h"
#include "afxdialogex.h"


// CEverageBlurDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEverageBlurDlg, CDialogEx)

CEverageBlurDlg::CEverageBlurDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EVERAGE_BLUR, pParent)
	, m_maskSize(0)
{

}

CEverageBlurDlg::~CEverageBlurDlg()
{
}

void CEverageBlurDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_maskSize);
	DDV_MinMaxInt(pDX, m_maskSize, 0, 30);
}


BEGIN_MESSAGE_MAP(CEverageBlurDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CEverageBlurDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CEverageBlurDlg �޽��� ó�����Դϴ�.


void CEverageBlurDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}


BOOL CEverageBlurDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
