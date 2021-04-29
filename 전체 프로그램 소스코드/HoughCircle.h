#pragma once
#include "afxcmn.h"


// CHoughCircle 대화 상자입니다.

class CHoughCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CHoughCircle)

public:
	CHoughCircle(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHoughCircle();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOUGH_CIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
