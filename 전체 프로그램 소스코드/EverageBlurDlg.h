#pragma once


// CEverageBlurDlg ��ȭ �����Դϴ�.

class CEverageBlurDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEverageBlurDlg)

public:
	CEverageBlurDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEverageBlurDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVERAGE_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_maskSize;
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
};
