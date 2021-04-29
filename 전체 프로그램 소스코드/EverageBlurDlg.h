#pragma once


// CEverageBlurDlg 대화 상자입니다.

class CEverageBlurDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEverageBlurDlg)

public:
	CEverageBlurDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEverageBlurDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVERAGE_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_maskSize;
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
};
