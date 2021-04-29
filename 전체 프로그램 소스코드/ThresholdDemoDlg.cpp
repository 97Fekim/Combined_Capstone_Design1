// ThresholdDemoDlg.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "ThresholdDemoDlg.h"
#include "afxdialogex.h"
#include "IppImage\IppImage.h"
#include "IppImage\IppConvert.h"
#include "IppImage\IppGeometry.h"
#include "IppImage\IppSegment.h"

// CThresholdDemoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CThresholdDemoDlg, CDialogEx)

CThresholdDemoDlg::CThresholdDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THRESHOLD_DEMO, pParent)
	, m_nThreshold(0)
{

}

CThresholdDemoDlg::~CThresholdDemoDlg()
{
}

void CThresholdDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THRESHOLD_SLIDER, m_sliderThreshold);
	DDX_Text(pDX, IDC_THRESHOLD_EDIT, m_nThreshold);
	DDV_MinMaxInt(pDX, m_nThreshold, 0, 255);
}


BEGIN_MESSAGE_MAP(CThresholdDemoDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_THRESHOLD_EDIT, &CThresholdDemoDlg::OnEnChangeThresholdEdit)
END_MESSAGE_MAP()


// CThresholdDemoDlg �޽��� ó�����Դϴ�.


BOOL CThresholdDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �����̴� ��Ʈ���� �ʱ�ȭ�Ѵ�.
	m_sliderThreshold.SetRange(0, 255);
	m_sliderThreshold.SetTicFreq(32);
	m_sliderThreshold.SetPageSize(32);
	m_sliderThreshold.SetPos(m_nThreshold);

	// ���� ��Ʈ���� ũ�⸦ ���Ѵ�.
	CRect rect;
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_PREVIEW);
	pImageWnd->GetClientRect(rect);

	// ���� ��Ʈ���� ũ�⿡ �°� �Է� ������ ���纻�� ũ�⸦ �����Ѵ�.
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppResizeNearest(imgSrc, imgDst, rect.Width(), rect.Height());
	IppImageToDib(imgDst, m_DibSrc);

	// �ʱ� �Ӱ谪�� ���� �̸����� ����ȭ ���� �����
	MakePreviewImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CThresholdDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// �����̵�ٿ��� �߻��� WM_HSCROLL �޽����� ��� ó��
	if (m_sliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderThreshold.GetPos();
		m_nThreshold = nPos;
		UpdateData(FALSE);

		// ���� ������ �Ӱ谪�� �̿��Ͽ� �̸����� ������ ����ȭ�� �����Ѵ�.
		MakePreviewImage();
		Invalidate(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CThresholdDemoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE_PREVIEW));
	m_DibRes.Draw(dcPreview.m_hDC, 0, 0);
}

void CThresholdDemoDlg::SetImage(IppDib& dib)
{
	m_DibSrc = dib;

	// �ݺ��� ����ȭ ����� �̿��� (�ʱ�) �Ӱ谪 ����
	IppByteImage imgSrc;
	IppDibToImage(m_DibSrc, imgSrc);
	m_nThreshold = IppBinarizationIterative(imgSrc);
}

void CThresholdDemoDlg::MakePreviewImage()
{
	// ���� �Ӱ谪�� �̿��Ͽ� ����ȭ�� �̸����� ���� ����
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppBinarization(imgSrc, imgDst, m_nThreshold);
	IppImageToDib(imgDst, m_DibRes);
}

void CThresholdDemoDlg::OnEnChangeThresholdEdit()
{
	// ����Ʈ ��Ʈ�ѿ��� ���ڰ� �ٲ� ���, �����̴� ��Ʈ���� ��ġ�� �����Ѵ�.
	UpdateData(TRUE);
	m_sliderThreshold.SetPos(m_nThreshold);

	// ���� ������ �Ӱ谪�� �̿��Ͽ� �̸����� ������ ����ȭ�� �����Ѵ�.
	MakePreviewImage();
	Invalidate(FALSE);
}
