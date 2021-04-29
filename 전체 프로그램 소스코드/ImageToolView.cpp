
// ImageToolView.cpp : CImageToolView Ŭ������ ����
//
#pragma once
#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#pragma once
#include "MainFrm.h"
#include "ImageToolDoc.h"
#include "ImageToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolView

IMPLEMENT_DYNCREATE(CImageToolView, CScrollView)

BEGIN_MESSAGE_MAP(CImageToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, &CImageToolView::OnViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CImageToolView::OnUpdateViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CImageToolView::OnViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CImageToolView::OnUpdateViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CImageToolView::OnViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CImageToolView::OnUpdateViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, &CImageToolView::OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CImageToolView::OnUpdateViewZoom4)
	ON_COMMAND(ID_VIEW_ZOOM0_5, &CImageToolView::OnViewZoom05)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM0_5, &CImageToolView::OnUpdateViewZoom05)
	ON_COMMAND(ID_VIEW_ZOOM0_2, &CImageToolView::OnViewZoom02)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM0_2, &CImageToolView::OnUpdateViewZoom02)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_SELECT_ROI, &CImageToolView::OnSelectRoi)
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

// CImageToolView ����/�Ҹ�

CImageToolView::CImageToolView()
	: m_nZoom(1)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_bDrawMode = FALSE;
}

CImageToolView::~CImageToolView()
{
}

BOOL CImageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.


	return CScrollView::PreCreateWindow(cs);
}

// CImageToolView �׸���

void CImageToolView::OnDraw(CDC* pDC)
{
	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (pDoc->m_Dib.IsValid())
	{
		double w = pDoc->m_Dib.GetWidth();
		double h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w*m_nZoom, h*m_nZoom);
	}

}

void CImageToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	SetScrollSizeToFit();
}

void CImageToolView::SetScrollSizeToFit()
{
	CSize sizeTotal;

	CImageToolDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		double w = pDoc->m_Dib.GetWidth();
		double h = pDoc->m_Dib.GetHeight();

		sizeTotal.cx = w * m_nZoom;
		sizeTotal.cy = h * m_nZoom;
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}



// CImageToolView �μ�


void CImageToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CImageToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageToolView ����

#ifdef _DEBUG
void CImageToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolDoc* CImageToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolDoc)));
	return (CImageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolView �޽��� ó����


BOOL CImageToolView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(60, 70, 80));
	FillOutsideRect(pDC, &br);


	return TRUE;
}

void CImageToolView::OnViewZoom1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nZoom = 1;
	SetScrollSizeToFit();	// ��ũ�ѹ� ���� ������ �����ϴ� �Լ�
	Invalidate(TRUE);		// �� ������ �ٽ� �׸����� �ϴ� �Լ�
}

void CImageToolView::OnViewZoom2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom3()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom4()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom05()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nZoom = 0.5;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom02()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nZoom = 0.2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nZoom == 1);
}

void CImageToolView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nZoom == 2);
}

void CImageToolView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nZoom == 3);
}

void CImageToolView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nZoom == 4);
}

void CImageToolView::OnUpdateViewZoom05(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nZoom == 0.5);
}

void CImageToolView::OnUpdateViewZoom02(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nZoom == 0.2);
}

void CImageToolView::ShowImageInfo(CPoint point)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CImageToolDoc* pDoc = GetDocument();
	int w = pDoc->m_Dib.GetWidth();
	int h = pDoc->m_Dib.GetHeight();
	int c = pDoc->m_Dib.GetPaletteNums();

	CString strText;

	// ���¹ٿ� ���콺 ��ǥ ǥ��
	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
	{
		strText.Format(_T("Point with mouse : %d, %d"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}

	// ���¹ٿ� �̹��� ���� ǥ��
	if (c == 0)
	{
		strText.Format(_T("width : %d, height : %d c : 16M"), w, h);
	}
	else
	{
		strText.Format(_T("width : %d height : %d c : %d"), w, h, c);
	}
	pFrame->m_wndStatusBar.SetPaneText(1, strText);
}


void CImageToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ROI�� ù ��ǥ ���, �׸�����on
	if (theApp.m_ROIMode == TRUE)
	{
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
		
		CPoint pt = point + GetScrollPosition(); 
		theApp.m_x1 = pt.x / m_nZoom;
		theApp.m_y1 = pt.y / m_nZoom;
		m_bDrawMode = TRUE;
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CImageToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CPoint pt = point + GetScrollPosition();
	pt.x /= m_nZoom;
	pt.y /= m_nZoom;
	ShowImageInfo(pt);
	
	if (theApp.m_ROIMode == TRUE)
	{
		if (m_bDrawMode == TRUE)
		{
			CPoint pt2 = point + GetScrollPosition();
			theApp.m_x2 = pt2.x / m_nZoom;
			theApp.m_y2 = pt2.y / m_nZoom;
			CClientDC dc(this);
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_NOT);
			dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
			// ������ �簢���� �����.
			dc.SetROP2(R2_NOT);
			dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
		}
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CImageToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (theApp.m_ROIMode == TRUE)
	{
		CPoint pt = point + GetScrollPosition();

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		// �������� Ÿ���� �׸���.
		dc.SetROP2(R2_NOT);
		theApp.m_x2 = pt.x / m_nZoom;
		theApp.m_y2 = pt.y / m_nZoom;
		dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
		m_bDrawMode = FALSE;
		
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CImageToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);

	CScrollView::OnRButtonDown(nFlags, point);
}

void CImageToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
}

void CImageToolView::OnSelectRoi()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	theApp.m_ROIMode = TRUE;
	AfxMessageBox(_T("ROI ������ �����մϴ�.\n\n�̹����� ���콺 ���ʹ�ư�� ���� �巡�� �Ͻʽÿ�"),MB_OK,0);
}

void CImageToolView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_NOT);
	dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
	
	CScrollView::OnMButtonDown(nFlags, point);
}
