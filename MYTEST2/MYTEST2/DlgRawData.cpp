// DlgRawData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MYTEST2.h"
#include "DlgRawData.h"
#include "afxdialogex.h"


// CDlgRawData �Ի���

IMPLEMENT_DYNAMIC(CDlgRawData, CDialogEx)

CDlgRawData::CDlgRawData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRawData::IDD, pParent)
	, m_nGap(0)
	, m_nFrame(2),
	m_ImageType(0)
	, m_nOffset(0)
	, m_height(3072)
	, m_width(2560)
	, WhiteZero(FALSE)
	, LittleEndian(FALSE)
	, OpenFile(FALSE)
	, VirtualStack(FALSE)
{

}

CDlgRawData::~CDlgRawData()
{
}

void CDlgRawData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GapImg, m_nGap);
	DDX_Text(pDX, IDC_EDIT_NumberImg, m_nFrame);
	DDX_Text(pDX, IDC_EDIT_Offset, m_nOffset);
	DDX_Text(pDX, IDC_EDIT_Height, m_height);
	DDX_Text(pDX, IDC_EDIT_Width, m_width);
	DDX_CBIndex(pDX,IDC_COMBO_ImageType, m_ImageType);
	DDX_Check(pDX, IDC_CHECK_WhiteZero, WhiteZero);
	DDX_Check(pDX, IDC_CHECK_LittleEndian, LittleEndian);
	DDX_Check(pDX, IDC_CHECK_Filesfolder, OpenFile);
	DDX_Check(pDX, IDC_CHECK_VisualStack, VirtualStack);
}


BEGIN_MESSAGE_MAP(CDlgRawData, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_WhiteZero, &CDlgRawData::OnBnClickedCheckWhitezero)
	ON_BN_CLICKED(IDC_CHECK_LittleEndian, &CDlgRawData::OnBnClickedCheckLittleendian)
	ON_BN_CLICKED(IDC_CHECK_Filesfolder, &CDlgRawData::OnBnClickedCheckFilesfolder)
	ON_BN_CLICKED(IDC_CHECK_VisualStack, &CDlgRawData::OnBnClickedCheckVisualstack)
END_MESSAGE_MAP()


// CDlgRawData ��Ϣ�������


void CDlgRawData::OnBnClickedCheckWhitezero()
{
	WhiteZero=!WhiteZero;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgRawData::OnBnClickedCheckLittleendian()
{
	LittleEndian=!LittleEndian;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgRawData::OnBnClickedCheckFilesfolder()
{
	OpenFile=!OpenFile;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgRawData::OnBnClickedCheckVisualstack()
{
	VirtualStack=!VirtualStack;	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
