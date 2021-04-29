// ErodeDlg.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "ErodeDlg.h"
#include "afxdialogex.h"


// CErodeDlg ��ȭ �����Դϴ�.

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


// CErodeDlg �޽��� ó�����Դϴ�.


BOOL CErodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CErodeDlg::OnEnChangeErode()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}
