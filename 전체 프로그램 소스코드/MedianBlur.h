#pragma once


// CMedianBlur ��ȭ �����Դϴ�.

class CMedianBlur : public CDialogEx
{
	DECLARE_DYNAMIC(CMedianBlur)

public:
	CMedianBlur(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMedianBlur();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIAN_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_maskSize;
	afx_msg void OnEnChangeEdit2();
};
