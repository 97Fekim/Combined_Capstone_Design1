#pragma once
#include "afxcmn.h"
#include "IppImage\IppDib.h"

// CThresholdDemoDlg 대화 상자입니다.

class CThresholdDemoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThresholdDemoDlg)

public:
	CThresholdDemoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThresholdDemoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THRESHOLD_DEMO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
