// Changesize.cpp : 实现文件
//

#include "stdafx.h"
#include "MYTEST2.h"
#include "Changesize.h"
#include "afxdialogex.h"


// CChangesize 对话框

IMPLEMENT_DYNAMIC(CChangesize, CDialogEx)

CChangesize::CChangesize(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangesize::IDD, pParent)
	, m_Height(3072)
	, m_Width(2560)
{

}

CChangesize::~CChangesize()
{
}

void CChangesize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Height, m_Height);
	DDX_Text(pDX, IDC_EDIT_Width, m_Width);
}


BEGIN_MESSAGE_MAP(CChangesize, CDialogEx)
END_MESSAGE_MAP()


// CChangesize 消息处理程序
