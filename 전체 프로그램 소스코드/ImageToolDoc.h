
// ImageToolDoc.h : CImageToolDoc Ŭ������ �������̽�
//


#pragma once
#include ".\IppImage\IppDib.h"


class CImageToolDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageToolDoc();
	DECLARE_DYNCREATE(CImageToolDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// ��Ʈ�� ��ü
	IppDib m_Dib;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnImageInverse();
	afx_msg void OnBrightnessContrast();
	afx_msg void OnViewHistgram();
	afx_msg void OnInspectionVoid();
	afx_msg void OnSetRoi();
	afx_msg void OnCreatHistImg();
	afx_msg void OnEverageBlur();
	afx_msg void OnGaussianBlur();
	afx_msg void OnMedianBlur();
	afx_msg void OnLabling();
	afx_msg void OnSobelEdge();
	afx_msg void OnHoughcircle();
	afx_msg void OnStretchHist();
	afx_msg void OnEqualizeHist();
	afx_msg void OnAdaptiveMean();
	afx_msg void OnAdaptiveGaussian();
	afx_msg void OnOtsuThreshold();
	afx_msg void OnErode();
	afx_msg void OnDilate();
	afx_msg void OnThresholdDemo();
};
