#pragma once


// CErodeDlg 대화 상자입니다.

class CErodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErodeDlg)

public:
	CErodeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CErodeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ERODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeErode();
	int m;
};
