// DlgWidthandwinlevel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MYTEST2.h"
#include "DlgWidthandwinlevel.h"
#include "afxdialogex.h"
#include"MainFrm.h"

// DlgWidthandwinlevel �Ի���

IMPLEMENT_DYNAMIC(DlgWidthandwinlevel, CDialogEx)

DlgWidthandwinlevel::DlgWidthandwinlevel(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgWidthandwinlevel::IDD, pParent)
{

}
DlgWidthandwinlevel::DlgWidthandwinlevel(int maxV, int minV, CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgWidthandwinlevel::IDD, pParent)
{
	m_maxValue = maxV;
	m_minValue = minV;
	m_level=(minV+maxV)/2;
	m_width=maxV-minV;


}

DlgWidthandwinlevel::~DlgWidthandwinlevel()
{
}

void DlgWidthandwinlevel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WINWIDTH, m_Slider_Width);
	DDX_Control(pDX, IDC_WINLEVEL, m_Slider_Level);
}


BEGIN_MESSAGE_MAP(DlgWidthandwinlevel, CDialogEx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_WINLEVEL, &DlgWidthandwinlevel::OnNMReleasedcaptureWinlevel)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_WINWIDTH, &DlgWidthandwinlevel::OnNMReleasedcaptureWinwidth)
END_MESSAGE_MAP()


// DlgWidthandwinlevel ��Ϣ�������
BOOL  DlgWidthandwinlevel::OnInitDialog()
{
     	CDialogEx::OnInitDialog();

	m_Slider_Width.SetRange(0,4096);
	m_Slider_Level.SetRange(0,4096);
	m_Slider_Width.SetPos(m_minValue);
	m_Slider_Level.SetPos(m_maxValue);
	CString str1,str2;
	str1.Format(_T("%d"),m_level);
	str2.Format(_T("%d"),m_width);
	SetDlgItemText(IDC_level1,str1);
    SetDlgItemText(IDC_Width1,str2);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();//
	CView * pView = pFrame->GetActiveView();//��ȡ��ǰ����ָ��
		m_maxValue=m_level+m_width/2;
		m_minValue=m_level-m_width/2;

	if(pView!=NULL)
	{
		pView->PostMessage(WM_WinWidthLevel,(WPARAM)m_maxValue,(LPARAM)m_minValue);
	}

	return true;
}

void DlgWidthandwinlevel::OnNMReleasedcaptureWinlevel(NMHDR *pNMHDR, LRESULT *pResult)
{
		m_level=m_Slider_Level.GetPos();
		CString str1;
		str1.Format(_T("%d"),m_level);
		SetDlgItemText(IDC_level1,str1);
		CMDIFrameWnd*pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;//��ȡ����ָ��
		CMDIChildWnd *pChild = pFrame->MDIGetActive(); 
	   CView *pView = (CView *) pChild->GetActiveView();  
	   		m_maxValue=m_level+m_width/2;
		m_minValue=m_level-m_width/2;

	if(pView != NULL)  //��ȡ�˵�ǰ����ָ����ܷ�����Ϣ
		pView->PostMessage(WM_WinWidthLevel,(WPARAM)m_maxValue,(LPARAM)m_minValue);  //ʹ��PostMessage������Ϣ



	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void DlgWidthandwinlevel::OnNMReleasedcaptureWinwidth(NMHDR *pNMHDR, LRESULT *pResult)
{
		m_width=m_Slider_Width.GetPos();
		CString str2;
		str2.Format(_T("%d"),m_width);
		SetDlgItemText(IDC_Width1,str2);
		CMDIFrameWnd*pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;//��ȡ����ָ��
		CMDIChildWnd *pChild = pFrame->MDIGetActive(); 
	   CView *pView = (CView *) pChild->GetActiveView(); 
	   	m_maxValue=m_level+m_width/2;
		m_minValue=m_level-m_width/2;
	if(pView != NULL)  //��ȡ�˵�ǰ����ָ����ܷ�����Ϣ
		pView->PostMessage(WM_WinWidthLevel,(WPARAM)m_maxValue,(LPARAM)m_minValue);  //ʹ��PostMessage������Ϣ
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
