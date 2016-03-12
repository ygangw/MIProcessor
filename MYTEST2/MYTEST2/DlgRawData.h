#pragma once


// CDlgRawData 对话框

class CDlgRawData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRawData)

public:
	CDlgRawData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRawData();

// 对话框数据
	enum { IDD = IDD_RawData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
