
// MYTEST2View.cpp : CMYTEST2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MYTEST2.h"
#endif

#include "MYTEST2Doc.h"
#include "MYTEST2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMYTEST2View

IMPLEMENT_DYNCREATE(CMYTEST2View, CScrollView)

BEGIN_MESSAGE_MAP(CMYTEST2View,CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(LEVELANDWIDTH, &CMYTEST2View::OnLevelandwidth)
	ON_MESSAGE(WM_WinWidthLevel,&CMYTEST2View::OnProcessWidthlevel)
	ON_COMMAND(ID_32772, &CMYTEST2View::OnProcessSize)
	ON_COMMAND(ID_ToBig,&CMYTEST2View::ToBig)
	ON_COMMAND(ID_ToSmall,&CMYTEST2View::ToSmall)
END_MESSAGE_MAP()

// CMYTEST2View 构造/析构

CMYTEST2View::CMYTEST2View()
{
	// TODO: 在此处添加构造代码

}

CMYTEST2View::~CMYTEST2View()
{
}

BOOL CMYTEST2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMYTEST2View 绘制

void CMYTEST2View::OnDraw(CDC* pDC)
{
	CMYTEST2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);
	if (rect.Width()<=1 || rect.Height()<=1)
		return;

	if (!pDoc->m_pPic.IsNull())
	{
		pDoc->m_pPic.Draw(pDC->m_hDC, 0, 0);

		//SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);
		//pDoc->m_pPic.Draw(pDC->m_hDC, rect);//将图片指定的区域内
	}
	// TODO: 在此处为本机数据添加绘制代码
}
void CMYTEST2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CMYTEST2Doc *pDoc=GetDocument();
	CSize sizeTotal;
	if(!pDoc->m_pPic.IsNull())
	{

		sizeTotal.cx=pDoc->m_pPic.GetWidth();
		sizeTotal.cy= pDoc->m_pPic.GetHeight();

	}
	else
	{
		sizeTotal.cx=2500;
		sizeTotal.cy=2500;
	}
	SetScrollSizes(MM_TEXT, sizeTotal );
}


// CMYTEST2View 打印

BOOL CMYTEST2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMYTEST2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMYTEST2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMYTEST2View 诊断

#ifdef _DEBUG
void CMYTEST2View::AssertValid() const
{
	CView::AssertValid();
}

void CMYTEST2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMYTEST2Doc* CMYTEST2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYTEST2Doc)));
	return (CMYTEST2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMYTEST2View 消息处理程序
LRESULT  CMYTEST2View::OnProcessWidthlevel(WPARAM wParam,LPARAM lParam)
{ 
	int maxV=(int)wParam;
	int minV=(int)lParam;
   CMYTEST2Doc* pDoc = GetDocument();
   Mat m_dstRGB=pDoc->m_srcRGB;
	pDoc->Mat16bToCImage(maxV, minV,m_dstRGB);

	Invalidate();

	return 0;

}

void CMYTEST2View::OnLevelandwidth()
{
    CMYTEST2Doc*pDoc=GetDocument();
	DlgWidthandwinlevel *Dlg=new DlgWidthandwinlevel(pDoc->m_srcMaxValue,pDoc->m_srcMinValue);
	if(Dlg->DoModal()==IDOK)
	{
	   Mat m_dstRGB=pDoc->m_srcRGB;
		pDoc->Mat16bToCImage(Dlg->m_maxValue,Dlg->m_minValue,m_dstRGB);
	}
	else
	{
		   Mat m_dstRGB=pDoc->m_srcRGB;
	pDoc->Mat16bToCImage(pDoc->m_srcMaxValue,pDoc->m_srcMinValue,m_dstRGB);
	}
	delete Dlg;

	Invalidate();
	// TODO: 在此添加命令处理程序代码
}


void CMYTEST2View::OnProcessSize()
{
	CMYTEST2Doc* pDoc = GetDocument();
	pDoc->ChangeSize();
    OnInitialUpdate();
	Invalidate();// TODO: 在此添加命令处理程序代码
}
void  CMYTEST2View::ToBig()
{
	CMYTEST2Doc* pDoc = GetDocument();
	pDoc->ToBig();
    OnInitialUpdate();
	Invalidate();

}
void  CMYTEST2View::ToSmall()
{
	CMYTEST2Doc* pDoc = GetDocument();
	pDoc->ToSmall();
    OnInitialUpdate();
	Invalidate();

}