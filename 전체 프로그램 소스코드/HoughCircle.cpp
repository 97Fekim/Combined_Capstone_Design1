// HoughCircle.cpp : 구현 파일입니다.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "HoughCircle.h"
#include "afxdialogex.h"


// CHoughCircle 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHoughCircle, CDialogEx)

CHoughCircle::CHoughCircle(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOUGH_CIRCLE, pParent)
	, m_Accuracy(0)
	, m_Circle2Circle(0)
	, m_minRadius(0)
	, m_maxRadius(0)
{

}

CHoughCircle::~CHoughCircle()
{
}

void CHoughCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ACCURACY, m_Accuracy);
	DDV_MinMaxInt(pDX, m_Accuracy, 1, 100);
	DDX_Control(pDX, IDC_ACCURACY_SLIDER, m_sliderAccuracy);
	DDX_Text(pDX, IDC_CIRCLE2CIRCLE, m_Circle2Circle);
	DDV_MinMaxInt(pDX, m_Circle2Circle, 1, 100);
	DDX_Control(pDX, IDC_CIRCLE2CIRCLE_SLIDER, m_sliderCircle2Circle);
	DDX_Text(pDX, IDC_MIN_RADIUS, m_minRadius);
	DDV_MinMaxInt(pDX, m_minRadius, 0, 100);
	DDX_Control(pDX, IDC_MIN_RADIUS_SLIDER, m_sliderMinRadius);
	DDX_Text(pDX, IDC_MAX_RADIUS, m_maxRadius);
	DDV_MinMaxInt(pDX, m_maxRadius, 0, 100);
	DDX_Control(pDX, IDC_MAX_RADIUS_SLIDER, m_sliderMaxRadius);
}


BEGIN_MESSAGE_MAP(CHoughCircle, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_ACCURACY, &CHoughCircle::OnEnChangeAccuracy)
	ON_EN_CHANGE(IDC_CIRCLE2CIRCLE, &CHoughCircle::OnEnChangeCircle2circle)
	ON_EN_CHANGE(IDC_MIN_RADIUS, &CHoughCircle::OnEnChangeMinRadius)
	ON_EN_CHANGE(IDC_MAX_RADIUS, &CHoughCircle::OnEnChangeMaxRadius)
END_MESSAGE_MAP()


// CHoughCircle 메시지 처리기입니다.


BOOL CHoughCircle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_sliderAccuracy.SetRange(1, 100);
	m_sliderAccuracy.SetTicFreq(32);
	m_sliderAccuracy.SetPageSize(12);

	m_sliderCircle2Circle.SetRange(1, 100);
	m_sliderCircle2Circle.SetTicFreq(32);
	m_sliderCircle2Circle.SetPageSize(12);

	m_sliderMinRadius.SetRange(0, 100);
	m_sliderMinRadius.SetTicFreq(32);
	m_sliderMinRadius.SetPageSize(12);

	m_sliderMaxRadius.SetRange(0, 100);
	m_sliderMaxRadius.SetTicFreq(32);
	m_sliderMaxRadius.SetPageSize(12);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHoughCircle::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderAccuracy.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_Accuracy = m_sliderAccuracy.GetPos();
		UpdateData(FALSE);
	}

	if (m_sliderCircle2Circle.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_Circle2Circle = m_sliderCircle2Circle.GetPos();
		UpdateData(FALSE);
	}

	if (m_sliderMinRadius.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_minRadius = m_sliderMinRadius.GetPos();
		UpdateData(FALSE);
	}

	if (m_sliderMaxRadius.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_maxRadius = m_sliderMaxRadius.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CHoughCircle::OnEnChangeAccuracy()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderAccuracy.SetPos(m_Accuracy);
}


void CHoughCircle::OnEnChangeCircle2circle()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderCircle2Circle.SetPos(m_Circle2Circle);
}


void CHoughCircle::OnEnChangeMinRadius()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderMinRadius.SetPos(m_minRadius);
}


void CHoughCircle::OnEnChangeMaxRadius()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderMaxRadius.SetPos(m_maxRadius);
}
