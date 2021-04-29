#pragma once


// CMedianBlur 대화 상자입니다.

class CMedianBlur : public CDialogEx
{
	DECLARE_DYNAMIC(CMedianBlur)

public:
	CMedianBlur(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMedianBlur();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIAN_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_maskSize;
	afx_msg void OnEnChangeEdit2();
};
