// HoughCircle.cpp : ���� �����Դϴ�.
//
#pragma once
#include "stdafx.h"
#include "ImageTool.h"
#include "HoughCircle.h"
#include "afxdialogex.h"


// CHoughCircle ��ȭ �����Դϴ�.

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


// CHoughCircle �޽��� ó�����Դϴ�.


BOOL CHoughCircle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CHoughCircle::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderAccuracy.SetPos(m_Accuracy);
}


void CHoughCircle::OnEnChangeCircle2circle()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderCircle2Circle.SetPos(m_Circle2Circle);
}


void CHoughCircle::OnEnChangeMinRadius()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderMinRadius.SetPos(m_minRadius);
}


void CHoughCircle::OnEnChangeMaxRadius()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderMaxRadius.SetPos(m_maxRadius);
}
