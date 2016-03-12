
// MYTEST2Doc.h : CMYTEST2Doc ��Ľӿ�
//


#pragma once
#include "DlgWidthandwinlevel.h"
#include"DlgRawData.h"
#include"Changesize.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include"opencv2/opencv.hpp"
using namespace cv;
using namespace std;
typedef enum
{IMAGE_TYPE_16BITS,
	IMAGE_TYPE_8BITS
	
} ImageType;

class CMYTEST2Doc : public CDocument
{
protected: // �������л�����
	CMYTEST2Doc();
	DECLARE_DYNCREATE(CMYTEST2Doc)

// ����
public:
	BOOL bChange;//��¼ͼ���С�ı䣻
	Mat m_srcRGB;
	Mat Dst;
	CImage m_pPic;
	UINT m_srcWidth;
	UINT m_srcHeight;
	int m_srcType;
	int m_srcMaxValue;	// �Ҷ�ӳ�����ֵ���������ݴ���m_srcMaxValue������255��ʾ��ȱʡֵ16383�Ǳ���ԭͼ���ֵ����ֵ
	int m_srcMinValue;	// �Ҷ�ӳ����Сֵ����������xiao��m_srcMinValue������0��ʾ��ȱʡֵ0�Ǳ���ԭͼ���ֵ���Сֵ
	LONGLONG  m_nMaxCurrentFrm;
    LONGLONG  m_nCurrentFrm;
	BOOL bWhiteZero;
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMYTEST2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
		virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	string CString2StdString(const CString& cstr);
	CString GetFileExt(const CString &str);

public:
	void Mat8bToCImage();
	void Mat16bToCImage(int maxV, int minV,Mat dst,BOOL bWhiteZero=FALSE);
	void ChangeSize();
	void SizeSelect(Size GetS);
	void ToBig();
	void ToSmall();
	afx_msg void OnSrcrgb();
	afx_msg void OnUpdateSrcrgb(CCmdUI *pCmdUI);
};
