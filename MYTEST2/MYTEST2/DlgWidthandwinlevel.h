#pragma once
#include "afxcmn.h"

// DlgWidthandwinlevel �Ի���

class DlgWidthandwinlevel : public CDialogEx
{
	DECLARE_DYNAMIC(DlgWidthandwinlevel)

public:
	DlgWidthandwinlevel(CWnd* pParent = NULL);   // ��׼���캯��
	DlgWidthandwinlevel(int maxV,int minV,CWnd* pParent = NULL);//���ع��캯��
	virtual ~DlgWidthandwinlevel();
 int m_minValue,m_maxValue;
int m_level,m_width;
// �Ի�������
	enum { IDD = IDD_ONWIDTTHANDLEVEL };

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureWinlevel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureWinwidth(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_Slider_Width;
	CSliderCtrl m_Slider_Level;
};
