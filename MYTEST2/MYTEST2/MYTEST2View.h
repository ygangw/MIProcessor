
// MYTEST2View.h : CMYTEST2View ��Ľӿ�
//

#pragma once
#include "DlgWidthandwinlevel.h"

class CMYTEST2View : public CScrollView
{
protected: // �������л�����
	CMYTEST2View();
	DECLARE_DYNCREATE(CMYTEST2View)

// ����
public:
	CMYTEST2Doc* GetDocument() const;

// ����
public:
	
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMYTEST2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
virtual void OnInitialUpdate();
protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLevelandwidth();
	afx_msg LRESULT  OnProcessWidthlevel(WPARAM wParam,LPARAM lParam);
	afx_msg void OnProcessSize();
	afx_msg void ToBig();
	afx_msg void ToSmall();
};

#ifndef _DEBUG  // MYTEST2View.cpp �еĵ��԰汾
inline CMYTEST2Doc* CMYTEST2View::GetDocument() const
   { return reinterpret_cast<CMYTEST2Doc*>(m_pDocument); }
#endif

