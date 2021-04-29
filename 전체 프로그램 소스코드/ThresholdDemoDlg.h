#pragma once
#include "afxcmn.h"
#include "IppImage\IppDib.h"

// CThresholdDemoDlg ��ȭ �����Դϴ�.

class CThresholdDemoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThresholdDemoDlg)

public:
	CThresholdDemoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CThresholdDemoDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THRESHOLD_DEMO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderThreshold;
	int m_nThreshold;

	IppDib m_DibSrc;
	IppDib m_DibRes;
	void SetImage(IppDib& dib);
	void MakePreviewImage();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnEnChangeThresholdEdit();
};
