
// MYTEST2View.cpp : CMYTEST2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(LEVELANDWIDTH, &CMYTEST2View::OnLevelandwidth)
	ON_MESSAGE(WM_WinWidthLevel,&CMYTEST2View::OnProcessWidthlevel)
	ON_COMMAND(ID_32772, &CMYTEST2View::OnProcessSize)
	ON_COMMAND(ID_ToBig,&CMYTEST2View::ToBig)
	ON_COMMAND(ID_ToSmall,&CMYTEST2View::ToSmall)
END_MESSAGE_MAP()

// CMYTEST2View ����/����

CMYTEST2View::CMYTEST2View()
{
	// TODO: �ڴ˴���ӹ������

}

CMYTEST2View::~CMYTEST2View()
{
}

BOOL CMYTEST2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMYTEST2View ����

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
		//pDoc->m_pPic.Draw(pDC->m_hDC, rect);//��ͼƬָ����������
	}
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CMYTEST2View ��ӡ

BOOL CMYTEST2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMYTEST2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMYTEST2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMYTEST2View ���

#ifdef _DEBUG
void CMYTEST2View::AssertValid() const
{
	CView::AssertValid();
}

void CMYTEST2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMYTEST2Doc* CMYTEST2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYTEST2Doc)));
	return (CMYTEST2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMYTEST2View ��Ϣ�������
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
	// TODO: �ڴ���������������
}


void CMYTEST2View::OnProcessSize()
{
	CMYTEST2Doc* pDoc = GetDocument();
	pDoc->ChangeSize();
    OnInitialUpdate();
	Invalidate();// TODO: �ڴ���������������
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