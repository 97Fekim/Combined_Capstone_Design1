#pragma once
#include "afxcmn.h"


// CInspectionVoidDlg 대화 상자입니다.

class CInspectionVoidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionVoidDlg)

public:
	CInspectionVoidDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInspectionVoidDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSPECTION_VOID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_thRatio;
	CSliderCtrl m_sliderthRatio;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditthratio();
};
