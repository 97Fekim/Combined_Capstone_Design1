#pragma once
#include "afxcmn.h"


// CFastInspectionDlg ��ȭ �����Դϴ�.

class CFastInspectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFastInspectionDlg)

public:
	CFastInspectionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFastInspectionDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAST_INSPECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderRatio;
	int m_Ratio;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditthratio();
};
