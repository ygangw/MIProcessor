#pragma once


// CDlgRawData �Ի���

class CDlgRawData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRawData)

public:
	CDlgRawData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRawData();

// �Ի�������
	enum { IDD = IDD_RawData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	public:
	LONGLONG m_nGap;
	LONGLONG m_nFrame;
	LONGLONG m_nOffset;
	int m_height;
	int m_width;
	int m_ImageType;
	BOOL WhiteZero;
	BOOL LittleEndian;
	BOOL OpenFile;
	BOOL VirtualStack;
	afx_msg void OnBnClickedCheckWhitezero();
	afx_msg void OnBnClickedCheckLittleendian();
	afx_msg void OnBnClickedCheckFilesfolder();
	afx_msg void OnBnClickedCheckVisualstack();
};
