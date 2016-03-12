
// MYTEST2View.h : CMYTEST2View 类的接口
//

#pragma once
#include "DlgWidthandwinlevel.h"

class CMYTEST2View : public CScrollView
{
protected: // 仅从序列化创建
	CMYTEST2View();
	DECLARE_DYNCREATE(CMYTEST2View)

// 特性
public:
	CMYTEST2Doc* GetDocument() const;

// 操作
public:
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMYTEST2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
virtual void OnInitialUpdate();
protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLevelandwidth();
	afx_msg LRESULT  OnProcessWidthlevel(WPARAM wParam,LPARAM lParam);
	afx_msg void OnProcessSize();
	afx_msg void ToBig();
	afx_msg void ToSmall();
};

#ifndef _DEBUG  // MYTEST2View.cpp 中的调试版本
inline CMYTEST2Doc* CMYTEST2View::GetDocument() const
   { return reinterpret_cast<CMYTEST2Doc*>(m_pDocument); }
#endif

