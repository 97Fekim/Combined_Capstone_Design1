// MedianBlur.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "MedianBlur.h"
#include "afxdialogex.h"


// CMedianBlur ��ȭ �����Դϴ�.

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


// CMedianBlur �޽��� ó�����Դϴ�.


BOOL CMedianBlur::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMedianBlur::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
}
