
// ImageTool.h : ImageTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CImageToolApp:
// �� Ŭ������ ������ ���ؼ��� ImageTool.cpp�� �����Ͻʽÿ�.
//

class IppDib;

class CImageToolApp : public CWinAppEx
{
public:
	CImageToolApp();

public:
	IppDib* m_pNewDib;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_ratio;

// �����Դϴ�.
	BOOL m_bHiColorIcons;
	BOOL m_ROIMode;
	BOOL m_fastInspectMode;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnFastInspect();
	afx_msg void OnFastInspectExit();
};

extern CImageToolApp theApp;

void AfxNewBitmap(IppDib& dib);
void AfxPrintInfo(CString message);
void AfxPrintInfo(LPCTSTR lpszFormat, ...);