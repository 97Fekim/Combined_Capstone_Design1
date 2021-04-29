
// ImageToolView.cpp : CImageToolView 클래스의 구현
//
#pragma once
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CImageToolView 생성/소멸

CImageToolView::CImageToolView()
	: m_nZoom(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bDrawMode = FALSE;
}

CImageToolView::~CImageToolView()
{
}

BOOL CImageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.


	return CScrollView::PreCreateWindow(cs);
}

// CImageToolView 그리기

void CImageToolView::OnDraw(CDC* pDC)
{
	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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



// CImageToolView 인쇄


void CImageToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageToolView 진단

#ifdef _DEBUG
void CImageToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolDoc* CImageToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolDoc)));
	return (CImageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolView 메시지 처리기


BOOL CImageToolView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(60, 70, 80));
	FillOutsideRect(pDC, &br);


	return TRUE;
}

void CImageToolView::OnViewZoom1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 1;
	SetScrollSizeToFit();	// 스크롤바 관련 설정을 수행하는 함수
	Invalidate(TRUE);		// 뷰 영역을 다시 그리도록 하는 함수
}

void CImageToolView::OnViewZoom2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom05()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 0.5;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnViewZoom02()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 0.2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CImageToolView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 1);
}

void CImageToolView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 2);
}

void CImageToolView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 3);
}

void CImageToolView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 4);
}

void CImageToolView::OnUpdateViewZoom05(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 0.5);
}

void CImageToolView::OnUpdateViewZoom02(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
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

	// 상태바에 마우스 좌표 표시
	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
	{
		strText.Format(_T("Point with mouse : %d, %d"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}

	// 상태바에 이미지 정보 표시
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// ROI의 첫 좌표 기억, 그리기모드on
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
			// 이전의 사각형을 지운다.
			dc.SetROP2(R2_NOT);
			dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
		}
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CImageToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (theApp.m_ROIMode == TRUE)
	{
		CPoint pt = point + GetScrollPosition();

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		// 최종적인 타원을 그린다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
}

void CImageToolView::OnSelectRoi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	theApp.m_ROIMode = TRUE;
	AfxMessageBox(_T("ROI 지정을 시작합니다.\n\n이미지에 마우스 왼쪽버튼을 눌러 드래그 하십시오"),MB_OK,0);
}

void CImageToolView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_NOT);
	dc.Rectangle(theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
	
	CScrollView::OnMButtonDown(nFlags, point);
}
