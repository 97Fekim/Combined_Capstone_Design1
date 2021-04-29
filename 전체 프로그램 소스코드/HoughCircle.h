#pragma once
#include "afxcmn.h"


// CHoughCircle ��ȭ �����Դϴ�.

class CHoughCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CHoughCircle)

public:
	CHoughCircle(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHoughCircle();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOUGH_CIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_Accuracy;
	CSliderCtrl m_sliderAccuracy;
	int m_Circle2Circle;
	CSliderCtrl m_sliderCircle2Circle;
	int m_minRadius;
	CSliderCtrl m_sliderMinRadius;
	int m_maxRadius;
	CSliderCtrl m_sliderMaxRadius;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeAccuracy();
	afx_msg void OnEnChangeCircle2circle();
	afx_msg void OnEnChangeMinRadius();
	afx_msg void OnEnChangeMaxRadius();
};
