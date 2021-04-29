// DilateDlg.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "DilateDlg.h"
#include "afxdialogex.h"


// CDilateDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDilateDlg, CDialogEx)

CDilateDlg::CDilateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DILATE, pParent)
	, m_maskSize(0)
{

}

CDilateDlg::~CDilateDlg()
{
}

void CDilateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DILATE, m_maskSize);
	DDV_MinMaxInt(pDX, m_maskSize, 3, 30);
}


BEGIN_MESSAGE_MAP(CDilateDlg, CDialogEx)
	ON_EN_CHANGE(IDC_DILATE, &CDilateDlg::OnEnChangeDilate)
END_MESSAGE_MAP()


// CDilateDlg �޽��� ó�����Դϴ�.


BOOL CDilateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDilateDlg::OnEnChangeDilate()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
}
