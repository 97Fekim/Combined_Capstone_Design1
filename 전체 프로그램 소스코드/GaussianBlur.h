#pragma once


// CGaussianBlur ��ȭ �����Դϴ�.

class CGaussianBlur : public CDialogEx
{
	DECLARE_DYNAMIC(CGaussianBlur)

public:
	CGaussianBlur(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGaussianBlur();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAUSSIAN_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_maskSize;
	afx_msg void OnEnChangeEdit1();
};
