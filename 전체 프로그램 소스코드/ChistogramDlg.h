#pragma once


// ChistogramDlg ��ȭ �����Դϴ�.

class ChistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChistogramDlg)

public:
	ChistogramDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ChistogramDlg();
	int m_Histogram[256];

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void SetImage(IppDib* pDib);
	afx_msg void OnPaint();
	afx_msg void OnStnClickedWidth();
};
