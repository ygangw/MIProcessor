#pragma once


// CChangesize 对话框

class CChangesize : public CDialogEx
{
	DECLARE_DYNAMIC(CChangesize)

public:
	CChangesize(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangesize();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Height;
	int m_Width;
};
