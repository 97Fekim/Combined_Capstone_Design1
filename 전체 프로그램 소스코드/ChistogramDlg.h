#pragma once


// ChistogramDlg 대화 상자입니다.

class ChistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChistogramDlg)

public:
	ChistogramDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ChistogramDlg();
	int m_Histogram[256];

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetImage(IppDib* pDib);
	afx_msg void OnPaint();
	afx_msg void OnStnClickedWidth();
};
