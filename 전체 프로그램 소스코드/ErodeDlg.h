#pragma once


// CErodeDlg ��ȭ �����Դϴ�.

class CErodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErodeDlg)

public:
	CErodeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CErodeDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ERODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeErode();
	int m;
};
