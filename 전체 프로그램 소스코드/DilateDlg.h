#pragma once


// CDilateDlg ��ȭ �����Դϴ�.

class CDilateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDilateDlg)

public:
	CDilateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDilateDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DILATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_maskSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeDilate();
};
