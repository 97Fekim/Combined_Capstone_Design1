#pragma once


// CDilateDlg 대화 상자입니다.

class CDilateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDilateDlg)

public:
	CDilateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDilateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DILATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_maskSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeDilate();
};
