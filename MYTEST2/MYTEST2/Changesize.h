#pragma once


// CChangesize �Ի���

class CChangesize : public CDialogEx
{
	DECLARE_DYNAMIC(CChangesize)

public:
	CChangesize(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangesize();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Height;
	int m_Width;
};
