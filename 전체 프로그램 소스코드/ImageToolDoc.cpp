
// ImageToolDoc.cpp : CImageToolDoc 클래스의 구현
//
#pragma once
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#include "FileNewDlg.h"
#endif

#pragma once
#include "ImageToolDoc.h"
#include "InspectionVoidDlg.h"
#include <string>

#include <propkey.h>
#include "IppImage\IppImage.h"
#include "IppImage\\IppConvert.h"
#include "IppImage\IppEnhance.h"
#include "IppImage\InspectionTool.h"

#include "EverageBlurDlg.h"
#include "BrightnessContrastDlg.h"
#include "ChistogramDlg.h"
#include "ThresholdDemoDlg.h"
#include "GaussianBlur.h"
#include "HoughCircle.h"
#include "ErodeDlg.h"
#include "DilateDlg.h"
#include "IppImage\IppSegment.h"
#include <opencv2/opencv.hpp>

using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib,img) \
	IppByteImage img; \
	IppDibToImage(m_Dib, img);

#define CONVERT_DIB_TO_RGBBYTEIMAGE(m_Dib,img) \
	IppRgbImage img; \
	IppDibToImage(m_Dib, img);

#define CONVERT_IMAGE_TO_DIB(img,dib) \
	IppDib dib; \
	IppImageToDib(img, dib);

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
	ON_COMMAND(ID_BRIGHTNESS_CONTRAST, &CImageToolDoc::OnBrightnessContrast)
	ON_COMMAND(ID_VIEW_HISTGRAM, &CImageToolDoc::OnViewHistgram)
	ON_COMMAND(ID_INSPECTION_VOID, &CImageToolDoc::OnInspectionVoid)
	ON_COMMAND(ID_SET_ROI, &CImageToolDoc::OnSetRoi)
	ON_COMMAND(ID_CREAT_HIST_IMG, &CImageToolDoc::OnCreatHistImg)
	ON_COMMAND(ID_EVERAGE_BLUR, &CImageToolDoc::OnEverageBlur)
	ON_COMMAND(ID_GAUSSIAN_BLUR, &CImageToolDoc::OnGaussianBlur)
	ON_COMMAND(ID_MEDIAN_BLUR, &CImageToolDoc::OnMedianBlur)
	ON_COMMAND(ID_LABLING, &CImageToolDoc::OnLabling)
	ON_COMMAND(ID_SOBEL_EDGE, &CImageToolDoc::OnSobelEdge)
	ON_COMMAND(ID_HOUGHCIRCLE, &CImageToolDoc::OnHoughcircle)
	ON_COMMAND(ID_STRETCH_HIST, &CImageToolDoc::OnStretchHist)
	ON_COMMAND(ID_EQUALIZE_HIST, &CImageToolDoc::OnEqualizeHist)
	ON_COMMAND(ID_ADAPTIVE_MEAN, &CImageToolDoc::OnAdaptiveMean)
	ON_COMMAND(ID_ADAPTIVE_GAUSSIAN, &CImageToolDoc::OnAdaptiveGaussian)
	ON_COMMAND(ID_OTSU_THRESHOLD, &CImageToolDoc::OnOtsuThreshold)
	ON_COMMAND(ID_ERODE, &CImageToolDoc::OnErode)
	ON_COMMAND(ID_DILATE, &CImageToolDoc::OnDilate)
	ON_COMMAND(ID_THRESHOLD_DEMO, &CImageToolDoc::OnThresholdDemo)
END_MESSAGE_MAP()


// CImageToolDoc 생성/소멸
CImageToolDoc::CImageToolDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	BOOL ret = TRUE;

	if(theApp.m_pNewDib == NULL)
	{

		CFileNewDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nType == 0)
				ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
			else
				ret = m_Dib.CreateRgbBitmap(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return ret;
}

// CImageToolDoc serialization
void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolDoc 진단
#ifdef _DEBUG
void CImageToolDoc::AssertValid() const

{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CImageToolDoc 명령
BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	BOOL res = m_Dib.Load(CT2A(lpszPathName));
	
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 불러올 수 없습니다."));
		return FALSE;
	}
	
	if (theApp.m_fastInspectMode)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, input)
			IppRgbImage Result;
		Result = InspectionVoid(input, theApp.m_ratio);
		CONVERT_IMAGE_TO_DIB(Result, dib)
			AfxPrintInfo(_T("[VOID Inspected] Input Image : %s"), GetTitle());
		AfxNewBitmap(dib);
	}
	else if (res)
	{
		AfxPrintInfo(_T("[File Open]"));
		AfxPrintInfo(_T("File Location : %s"), lpszPathName);
		AfxPrintInfo(_T("해상도 : %d x %d"), m_Dib.GetWidth(), m_Dib.GetHeight());
		AfxPrintInfo(_T("Bitcount : %d"), 0x01 << m_Dib.GetBitCount());

		/* 영상 불러오기 시 히스토그램 동시 출력 */
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, input)
		IppRgbImage Histogram_img;
		Histogram_img = getHistImg(input);
		CONVERT_IMAGE_TO_DIB(Histogram_img, dib)
		AfxPrintInfo(_T("[Hisogram Image created] Input Image : %s"), GetTitle());
		AfxNewBitmap(dib);

	}

	return res;
}

BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return m_Dib.Save(CT2A(lpszPathName));
}

void CImageToolDoc::OnWindowDuplicate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxNewBitmap(m_Dib);
}

void CImageToolDoc::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}

void CImageToolDoc::OnImageInverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)

	IppInverse(img);

	CONVERT_IMAGE_TO_DIB(img, dib)

	AfxPrintInfo(_T("[Inverse] Input Image : %s"), GetTitle());
	printf("/* Image Inversed */\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnBrightnessContrast()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}

	CBrightnessContrastDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppBrightness_Contrast(img, dlg.m_nContrast, dlg.m_nBrightness);
		CONVERT_IMAGE_TO_DIB(img, dib)

		AfxPrintInfo(_T("[Brightness and Contrast Modified] Input image : %s, \nBrightness : %d, \nContrast: %d%%"),
		GetTitle(), dlg.m_nBrightness, dlg.m_nContrast);
		printf("/* Image Enhanced */\nAlpha : %d\nBeta : %d\n\n", dlg.m_nBrightness, dlg.m_nContrast);
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnViewHistgram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	ChistogramDlg dlg;
	dlg.SetImage(&m_Dib);
	dlg.DoModal();
}

void CImageToolDoc::OnInspectionVoid()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 검사가 불가능합니다."));
		return;
	}
	CInspectionVoidDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, input)
		IppRgbImage Result;
		Result = InspectionVoid(input,dlg.m_thRatio);
		CONVERT_IMAGE_TO_DIB(Result, dib)
		AfxPrintInfo(_T("[VOID Inspected] Input Image : %s"), GetTitle());
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnSetRoi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	/* 도큐먼트의 이미지를 받아옴 */
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)

	/* 도큐먼트의 이미지 클래스를 Mat클래스로 변환 */
	BYTE** p = img.GetPixels2D();

	int cols = img.GetWidth();
	int rows = img.GetHeight();

	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}


	/* ROI이미지 생성 */
	Rect r(theApp.m_x1, theApp.m_y1, theApp.m_x2 - theApp.m_x1, theApp.m_y2 - theApp.m_y1);

	if (((theApp.m_x1 < theApp.m_x2) && (theApp.m_y1 > theApp.m_y2)))
		r = Rect(theApp.m_x1, theApp.m_y2, theApp.m_x2 - theApp.m_x1, theApp.m_y1 - theApp.m_y2);
	else if (((theApp.m_x1 > theApp.m_x2) && (theApp.m_y1 < theApp.m_y2)))
		r = Rect(theApp.m_x2, theApp.m_y1, theApp.m_x1 - theApp.m_x2, theApp.m_y2 - theApp.m_y1);
	else if (((theApp.m_x1 > theApp.m_x2) && (theApp.m_y1 > theApp.m_y2)))
		r = Rect(theApp.m_x2, theApp.m_y2, theApp.m_x1 - theApp.m_x2, theApp.m_y1 - theApp.m_y2);

	Mat ROI = src(r).clone();


	/* Mat 클래스의 ROI이미지를 출력을 위한 클래스로 변환 */
	IppByteImage ROI_img;
	ROI_img.CreateImage(ROI.cols, ROI.rows);
	BYTE** p_ROI = ROI_img.GetPixels2D();

	for (int row = 0; row < ROI.rows; ++row)
		for (int col = 0; col < ROI.cols; ++col)
		{
			p_ROI[row][col] = ROI.at<uchar>(row, col);
		}

	CONVERT_IMAGE_TO_DIB(ROI_img, dib)

	/* Info 출력 */
	AfxPrintInfo(_T("[ROI set]"), GetTitle());
	AfxPrintInfo(_T("Input Image : %s"), GetTitle());

	if (((theApp.m_x1 < theApp.m_x2) && (theApp.m_y1 > theApp.m_y2)))
	{		
		AfxPrintInfo(_T("Start Point : (%d,%d)"), theApp.m_x2, theApp.m_y1);
		AfxPrintInfo(_T("Width : %d"), theApp.m_x1 - theApp.m_x2);
		AfxPrintInfo(_T("Height : %d"), theApp.m_y2 - theApp.m_y1);
	}
	else if (((theApp.m_x1 > theApp.m_x2) && (theApp.m_y1 < theApp.m_y2)))
	{
		AfxPrintInfo(_T("Start Point : (%d,%d)"), theApp.m_x2, theApp.m_y1);
		AfxPrintInfo(_T("Width : %d"), theApp.m_x1 - theApp.m_x2);
		AfxPrintInfo(_T("Height : %d"), theApp.m_y2 - theApp.m_y1);
	}
	else if (((theApp.m_x1 > theApp.m_x2) && (theApp.m_y1 > theApp.m_y2)))
	{
		AfxPrintInfo(_T("Start Point : (%d,%d)"), theApp.m_x2, theApp.m_y2);
		AfxPrintInfo(_T("Width : %d"), theApp.m_x1 - theApp.m_x2);
		AfxPrintInfo(_T("Height : %d"), theApp.m_y1 - theApp.m_y2);
	}
	else
	{
		AfxPrintInfo(_T("Start Point : (%d,%d)"), theApp.m_x1, theApp.m_y1);
		AfxPrintInfo(_T("Width : %d"), theApp.m_x2 - theApp.m_x1);
		AfxPrintInfo(_T("Height : %d"), theApp.m_y2 - theApp.m_y1);
	}

	AfxNewBitmap(dib);
	printf("/* ROI set processed */\nStart point : (%d,%d)\nwidth : %d\nheight : %d\n\n", theApp.m_x1, theApp.m_y1, theApp.m_x2, theApp.m_y2);
	theApp.m_x1 = 0; theApp.m_y1 = 0; theApp.m_x2 = 0; theApp.m_y2 = 0;
	theApp.m_ROIMode = FALSE;
}

void CImageToolDoc::OnCreatHistImg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, input)
	IppRgbImage Histogram_img;

	Histogram_img = getHistImg(input);

	CONVERT_IMAGE_TO_DIB(Histogram_img, dib)

	AfxPrintInfo(_T("[Hisogram Image created] Input Image : %s"), GetTitle());
	printf("/* Histogram Image created */\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnEverageBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CEverageBlurDlg dlg; 
	
	if (dlg.DoModal() == IDOK)
	{
		if ((dlg.m_maskSize < 3) || (dlg.m_maskSize % 2 == 0))
		{
			AfxMessageBox(_T("1) mask 사이즈는 3 이상이어야 합니다.\n2) mask 사이즈는 홀수여야 합니다."));
			return;
		}
		
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, src)
		IppEverageBlur(src, dlg.m_maskSize);

		CONVERT_IMAGE_TO_DIB(src, dib)

		AfxPrintInfo(_T("[Everage blur processed] Input image : %s"), GetTitle());
		AfxPrintInfo(_T("Mask size : %d"), dlg.m_maskSize);
		printf("/* Everage blur processed */\nMask size : %d\n\n", dlg.m_maskSize);
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnGaussianBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CGaussianBlur dlg;

	if (dlg.DoModal() == IDOK)
	{
		if ((dlg.m_maskSize < 3)||(dlg.m_maskSize%2 == 0))
		{
			AfxMessageBox(_T("1) mask 사이즈는 3 이상이어야 합니다.\n2) mask 사이즈는 홀수여야 합니다."));
			return;
		}

		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, src)
			IppGaussianBlur(src, dlg.m_maskSize);

		CONVERT_IMAGE_TO_DIB(src, dib)

			AfxPrintInfo(_T("[Gaussian blur processed] Input image : %s"), GetTitle());
		AfxPrintInfo(_T("Mask size : %d"), dlg.m_maskSize);
		printf("[Gaussian blur processed]\nMask size : %d\n\n", dlg.m_maskSize);
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnMedianBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CGaussianBlur dlg;

	if (dlg.DoModal() == IDOK)
	{
		if ((dlg.m_maskSize < 3) || (dlg.m_maskSize % 2 == 0))
		{
			AfxMessageBox(_T("1) mask 사이즈는 3 이상이어야 합니다.\n2) mask 사이즈는 홀수여야 합니다."));
			return;
		}

		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, src)
			IppMedianBlur(src, dlg.m_maskSize);

		CONVERT_IMAGE_TO_DIB(src, dib)
			AfxPrintInfo(_T("[Median blur processed] Input image : %s"), GetTitle());
		AfxPrintInfo(_T("Mask size : %d"), dlg.m_maskSize);
		printf("/* Median blur processed */\nMask size : %d\n\n", dlg.m_maskSize);
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnLabling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, input)
	IppRgbImage Labled_img;
	AfxPrintInfo(_T("[Labled Image created] Input Image : %s"), GetTitle());
	printf("/* Labled Image created */\n");
	Labled_img = getLabledImage(input);
	CONVERT_IMAGE_TO_DIB(Labled_img, dib)
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnSobelEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)

	IppSobelEdge(img);

	CONVERT_IMAGE_TO_DIB(img, dib)

	AfxPrintInfo(_T("[Sobel Edge Image created] Input Image : %s"), GetTitle());
	printf("/* Sobel Edge Image created */\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnHoughcircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.if (m_Dib.GetBitCount() != 8)
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CHoughCircle dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, input)
		AfxPrintInfo(_T("[Hough circle image created] Input image : %s"), GetTitle());
		AfxPrintInfo(_T("Accuracy : %d%c of Input rows"), dlg.m_Accuracy, '%');
		AfxPrintInfo(_T("Center to center distance : %d%c of Input rows"), dlg.m_Circle2Circle, '%');
		AfxPrintInfo(_T("Mininum distance : %d%c of Input rows"), dlg.m_minRadius, '%');
		AfxPrintInfo(_T("Maximum distance : %d%c of Input rows"), dlg.m_maxRadius, '%');

		printf("/* Hough Circle Image created */\n");
		printf("Accuracy : %d%c of Input rows\n", dlg.m_Accuracy, '%');
		printf("Center to center distance : %d%c of Input rows\n", dlg.m_Circle2Circle, '%');
		printf("Mininum distance : %d%c of Input rows\n", dlg.m_minRadius, '%');
		printf("Maximum distance : %d%c of Input rows\n", dlg.m_maxRadius, '%');

		IppRgbImage HoughCircled;
		HoughCircled = getHoughCircleImage(input, dlg.m_Accuracy, dlg.m_Circle2Circle, dlg.m_minRadius, dlg.m_maxRadius);
		CONVERT_IMAGE_TO_DIB(HoughCircled, dib)
		

		AfxNewBitmap(dib);
	}
	
}

void CImageToolDoc::OnStretchHist()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppStretchHistogram(img);
	CONVERT_IMAGE_TO_DIB(img, dib)
		
	AfxPrintInfo(_T("[Hisogram Stretched]\nInput image : %s"), GetTitle());
	printf("/* Histogram Stretched */\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnEqualizeHist()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppEqualizeHistogram(img);
	CONVERT_IMAGE_TO_DIB(img, dib)
	
	AfxPrintInfo(_T("[Histogram Equalized] Input Image : %s"), GetTitle());
	printf("/* Histogram Equalized */\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnAdaptiveMean()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppThreshold_adaptiveMean(img);
	CONVERT_IMAGE_TO_DIB(img, dib)

		AfxPrintInfo(_T("[Mean Adaptive Thresholded] Input Image : %s"), GetTitle());
	printf("/* Mean Adaptive Thresholded */\nparam 1 : 11\nparam 2 : 2\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnAdaptiveGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppThreshold_adaptiveGaussian(img);
	CONVERT_IMAGE_TO_DIB(img, dib)

		AfxPrintInfo(_T("[Gaussian Adaptive Thresholded] Input Image : %s"), GetTitle());
	printf("/* Gaussian Adaptive Thresholded */\nparam 1 : 11\nparam 2 : 2\n\n");
	AfxNewBitmap(dib);
}

void CImageToolDoc::OnOtsuThreshold()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppThreshold_otsu(img);
	CONVERT_IMAGE_TO_DIB(img, dib)
		AfxPrintInfo(_T("[Otsu Thresholded] Input Image : %s"), GetTitle());
	printf("/* Otsu Thresholded */\n\n");

	AfxNewBitmap(dib);
}

void CImageToolDoc::OnErode()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}

	CErodeDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		if ((dlg.m < 3) || (dlg.m % 2 == 0))
		{
			AfxMessageBox(_T("1) mask 사이즈는 3 이상이어야 합니다.\n2) mask 사이즈는 홀수여야 합니다."));
			return;
		}

		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, src)
			IppErode(src, dlg.m);

		CONVERT_IMAGE_TO_DIB(src, dib)
			AfxPrintInfo(_T("[Erode processed] Input image : %s"), GetTitle());
		AfxPrintInfo(_T("Mask size : %d"), dlg.m);
		printf("/* Erode processed */\nMask size : %d\n\n", dlg.m);
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnDilate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}

	CDilateDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		if ((dlg.m_maskSize < 3) || (dlg.m_maskSize % 2 == 0))
		{
			AfxMessageBox(_T("1) mask 사이즈는 3 이상이어야 합니다.\n2) mask 사이즈는 홀수여야 합니다."));
			return;
		}

		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, src)
			IppDilate(src, dlg.m_maskSize);

		CONVERT_IMAGE_TO_DIB(src, dib)
			AfxPrintInfo(_T("[Dilate processed] Input image : %s"), GetTitle());
		AfxPrintInfo(_T("Mask size : %d"), dlg.m_maskSize);
		printf("/* Dilate processed */\nMask size : %d\n\n", dlg.m_maskSize);
		AfxNewBitmap(dib);
	}
}

void CImageToolDoc::OnThresholdDemo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.GetBitCount() != 8)
	{
		AfxMessageBox(_T("COLOR영상은 변환이 불가능합니다."));
		return;
	}
	CThresholdDemoDlg dlg;
	dlg.SetImage(m_Dib);
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
			IppByteImage imgRes;
		IppBinarization(img, imgRes, dlg.m_nThreshold);
		CONVERT_IMAGE_TO_DIB(imgRes, dib)

			AfxPrintInfo(_T("[Image Thresholded] Input image : %s, th_Value : %d"), GetTitle(), dlg.m_nThreshold);
		AfxNewBitmap(dib);
		printf("/* Otsu Thresholded */\nthreshold value : %d\n\n",dlg.m_nThreshold);
	}
}

