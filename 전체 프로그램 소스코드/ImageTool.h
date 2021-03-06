
// ImageTool.h : ImageTool 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CImageToolApp:
// 이 클래스의 구현에 대해서는 ImageTool.cpp을 참조하십시오.
//

class IppDib;

class CImageToolApp : public CWinAppEx
{
public:
	CImageToolApp();

public:
	IppDib* m_pNewDib;

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	int m_ratio;

// 구현입니다.
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