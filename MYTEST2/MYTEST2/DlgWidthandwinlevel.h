#pragma once
#include "afxcmn.h"

// DlgWidthandwinlevel 对话框

class DlgWidthandwinlevel : public CDialogEx
{
	DECLARE_DYNAMIC(DlgWidthandwinlevel)

public:
	DlgWidthandwinlevel(CWnd* pParent = NULL);   // 标准构造函数
	DlgWidthandwinlevel(int maxV,int minV,CWnd* pParent = NULL);//重载构造函数
	virtual ~DlgWidthandwinlevel();
 int m_minValue,m_maxValue;
int m_level,m_width;
// 对话框数据
	enum { IDD = IDD_ONWIDTTHANDLEVEL };

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureWinlevel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureWinwidth(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_Slider_Width;
	CSliderCtrl m_Slider_Level;
};
