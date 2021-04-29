// GaussianBlur.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "GaussianBlur.h"
#include "afxdialogex.h"


// CGaussianBlur ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGaussianBlur, CDialogEx)

CGaussianBlur::CGaussianBlur(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAUSSIAN_BLUR, pParent)
	, m_maskSize(0)
{

}

CGaussianBlur::~CGaussianBlur()
{
}

void CGaussianBlur::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_maskSize);
	DDV_MinMaxInt(pDX, m_maskSize, 3, 30);
}


BEGIN_MESSAGE_MAP(CGaussianBlur, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CGaussianBlur::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CGaussianBlur �޽��� ó�����Դϴ�.


BOOL CGaussianBlur::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CGaussianBlur::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}
