// ChistogramDlg.cpp : 구현 파일입니다.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "ChistogramDlg.h"
#include "afxdialogex.h"
#include "IppImage\IppDib.h"
#include "IppImage\IppImage.h"
#include "IppImage\IppConvert.h"
#include "IppImage\IppEnhance.h"


// ChistogramDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ChistogramDlg, CDialogEx)

ChistogramDlg::ChistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{
	memset(m_Histogram, 0, sizeof(int) * 256);
}

ChistogramDlg::~ChistogramDlg()
{
}

void ChistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChistogramDlg, CDialogEx)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_WIDTH, &ChistogramDlg::OnStnClickedWidth)
END_MESSAGE_MAP()


// ChistogramDlg 메시지 처리기입니다.

void ChistogramDlg::SetImage(IppDib* pDib)
{
	if (pDib != NULL && pDib->GetBitCount() == 8)
	{
		IppByteImage img;
		IppDibToImage(*pDib, img);

		// 정규화된 히스토그램을 구한다.
		float histo[256] = { 0.f, };
		IppHistogram(img, histo);

		// 정규화된 히스토그램에서 최대값을 구한다.
		float max_histo = histo[0];
		for (int i = 1; i < 256; i++)
			if (histo[i] > max_histo) max_histo = histo[i];

		// m_Histogram 배열의 최대값이 100이 되도록 전체 배열의 값을 조절한다.
		for (int i = 0; i < 256; i++)
		{
			m_Histogram[i] = static_cast<int>(histo[i] * 100 / max_histo);
		}
	}
	else
	{
		memset(m_Histogram, 0, sizeof(int) * 256);
	}
}



void ChistogramDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CGdiObject* pOldPen = dc.SelectStockObject(DC_PEN);

	// 히스토그램 박스
	dc.SetDCPenColor(RGB(128, 128, 128));
	dc.MoveTo(20, 20);
	dc.LineTo(20, 120);
	dc.LineTo(275, 120);
	dc.LineTo(275, 20);

	// 각 그레이스케일에 해당하는 히스토그램 출력
	dc.SetDCPenColor(RGB(0, 0, 0));
	for (int i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + i, 120);
		dc.LineTo(20 + i, 120 - m_Histogram[i]);
	}

	// 그레이스케일 레벨 출력
	for (int i = 0; i < 256; i++)
	{
		dc.SetDCPenColor(RGB(i, i, i));
		dc.MoveTo(20 + i, 130);
		dc.LineTo(20 + i, 145);
	}

	dc.SelectObject(pOldPen);
}

void ChistogramDlg::OnStnClickedWidth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
