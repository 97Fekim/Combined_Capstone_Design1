#pragma once
#include "afxcmn.h"


// CInspectionVoidDlg ��ȭ �����Դϴ�.

class CInspectionVoidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionVoidDlg)

public:
	CInspectionVoidDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInspectionVoidDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSPECTION_VOID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_thRatio;
	CSliderCtrl m_sliderthRatio;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditthratio();
};
