
// MYTEST2Doc.h : CMYTEST2Doc 类的接口
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
protected: // 仅从序列化创建
	CMYTEST2Doc();
	DECLARE_DYNCREATE(CMYTEST2Doc)

// 特性
public:
	BOOL bChange;//记录图像大小改变；
	Mat m_srcRGB;
	Mat Dst;
	CImage m_pPic;
	UINT m_srcWidth;
	UINT m_srcHeight;
	int m_srcType;
	int m_srcMaxValue;	// 灰度映射最大值，即若数据大于m_srcMaxValue，就以255显示，缺省值16383是遍历原图后发现的最大值
	int m_srcMinValue;	// 灰度映射最小值，即若数据xiao于m_srcMinValue，就以0显示，缺省值0是遍历原图后发现的最小值
	LONGLONG  m_nMaxCurrentFrm;
    LONGLONG  m_nCurrentFrm;
	BOOL bWhiteZero;
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMYTEST2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
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
