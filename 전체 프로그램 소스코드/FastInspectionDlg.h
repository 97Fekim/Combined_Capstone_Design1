#pragma once
#include "afxcmn.h"


// CFastInspectionDlg 대화 상자입니다.

class CFastInspectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFastInspectionDlg)

public:
	CFastInspectionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFastInspectionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAST_INSPECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderRatio;
	int m_Ratio;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditthratio();
};
