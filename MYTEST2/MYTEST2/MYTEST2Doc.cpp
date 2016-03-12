
// MYTEST2Doc.cpp : CMYTEST2Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MYTEST2.h"
#endif

#include "MYTEST2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMYTEST2Doc

IMPLEMENT_DYNCREATE(CMYTEST2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMYTEST2Doc, CDocument)

	ON_COMMAND(ID_SRCRGB, &CMYTEST2Doc::OnSrcrgb)
	ON_UPDATE_COMMAND_UI(ID_SRCRGB, &CMYTEST2Doc::OnUpdateSrcrgb)
END_MESSAGE_MAP()


// CMYTEST2Doc 构造/析构

CMYTEST2Doc::CMYTEST2Doc()
{		m_srcWidth	= 2560;
	m_srcHeight	= 3072;
	m_srcType	= CV_16UC1;
	m_srcMaxValue = 4096;
	m_srcMinValue = 0;
	m_nCurrentFrm=0;// TODO: 在此添加一次性构造代码
    m_nMaxCurrentFrm=0;
	bChange=0;

}

CMYTEST2Doc::~CMYTEST2Doc()
{
}

BOOL CMYTEST2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMYTEST2Doc 序列化

void CMYTEST2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMYTEST2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMYTEST2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMYTEST2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMYTEST2Doc 诊断

#ifdef _DEBUG
void CMYTEST2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMYTEST2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMYTEST2Doc 命令
BOOL CMYTEST2Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if(GetFileExt(lpszPathName).CompareNoCase(_T("")) == 0)	// 打开数据文件
	{
        CDlgRawData Dlg;
		if(Dlg.DoModal()==IDOK)
		{
			
			switch((ImageType)Dlg.m_ImageType)
	{
	case IMAGE_TYPE_8BITS:
		m_srcType = CV_8UC1;
		break;
	case IMAGE_TYPE_16BITS:
		m_srcType = CV_16UC1;
		break;
	default:
		break;
	}
	m_srcWidth=Dlg.m_width;
	m_srcHeight=Dlg.m_height;
	LONGLONG m_nGap=Dlg.m_nGap;
	LONGLONG m_nOffset=Dlg.m_nOffset;
	BOOL LittleEndian=Dlg.LittleEndian;
	bWhiteZero=Dlg.WhiteZero;
    m_nMaxCurrentFrm=Dlg.m_nFrame;
	

		CFile pFile;
		if(pFile.Open(lpszPathName, CFile::modeRead |CFile::typeBinary)==FALSE)
		{

			MessageBox(NULL, TEXT("Wrong file!"), TEXT("Open"), MB_OK);
			return  FALSE;
		}

		if (m_srcRGB.empty()==false)	// 如果img已分配空间
		{
			if (m_srcRGB.cols!=m_srcWidth || m_srcRGB.rows!=m_srcHeight || m_srcRGB.type()!=m_srcType)
			{
				m_srcRGB.release();	// 如果宽高或类型不相符，删除重新分配
				m_srcRGB.create(m_srcHeight, m_srcWidth, m_srcType); // 创建图像缓存
			}
		}
		else
			m_srcRGB.create(m_srcHeight, m_srcWidth, m_srcType); // 创建缓存


		// 图像像素数
		UINT nPixel = m_srcHeight*m_srcWidth;
		UINT i, j;
		
			// 指向帧数据位置
   LONGLONG pos = m_nOffset+m_nCurrentFrm*(m_nGap+nPixel*sizeof(ushort)); // 首帧前的偏移+当前帧数*(帧间隔区+每帧大小)
	LONGLONG sizebuff = pFile.Seek(pos, CFile::begin);//文件移动到特定的偏移量
	
		ushort *pSource = new ushort[nPixel];
		pFile.Read(pSource,nPixel*sizeof(ushort));  

		// 医学图像大部分在0——4096之间
		m_srcMaxValue = 4096;
		m_srcMinValue = 0;
	

		// 将数据导入Mat中
		for (i=0; i<m_srcHeight; i++)  
		{  
			ushort *ps = m_srcRGB.ptr<ushort>(i);
			for (j=0 ; j<m_srcWidth; j++)  
			{  
				ps[j] = ushort(pSource[i*m_srcWidth+j]);
			}   
		} 

		delete []pSource;
		pFile.Close();
	
		if (m_srcRGB.empty())
		{
			MessageBox(NULL, TEXT("装载图像文件失败!"), TEXT("Open"), MB_OK);
			return FALSE;
		}
	Mat m_dstRGB=m_srcRGB;
		Dst=m_srcRGB;
		//保存至CImage中供显示
		m_pPic.Destroy();
		Mat16bToCImage(m_srcMaxValue, m_srcMinValue,m_dstRGB,bWhiteZero);	// 专用于16bit数据文件
	}	
	}
	else	// 打开普通图像
	{
		string pathname = CString2StdString(lpszPathName);
		m_srcRGB = imread(pathname);

		if (m_srcRGB.empty())
		{
			MessageBox(NULL, TEXT("装载图像文件失败!"), TEXT("Open"), MB_OK);
			return FALSE;
		}
		//保存至CImage中供显示
		m_pPic.Destroy();
		Mat8bToCImage();	// 用于8bit普通图像
	}


	return TRUE;
}

void CMYTEST2Doc::Mat8bToCImage()  
{  

	Mat m_dstRGB=m_srcRGB;
	int width = m_dstRGB.cols;
	int height = m_dstRGB.rows;  
	int channels = m_dstRGB.channels();  

	m_pPic.Destroy();//这一步是防止重复利用造成内存问题  
	m_pPic.Create(width,height,8*channels);  

	uchar* ps;  
	uchar* pimg = (uchar*)m_pPic.GetBits(); //获取CImage的像素存贮区的指针  
	int step = m_pPic.GetPitch();//每行的字节数,注意这个返回值有正有负  

	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置    
	// CImage中内置了调色板，我们要对他进行赋值：  
	if (1 == channels)  
	{  
		RGBQUAD* ColorTable;    
		int MaxColors=256;    
		//这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)    
		ColorTable = new RGBQUAD[MaxColors];    
		m_pPic.GetColorTable(0,MaxColors,ColorTable);//取得调色板指针    
		for (int i=0; i<MaxColors; i++)    
		{    
			ColorTable[i].rgbBlue = (BYTE)i;      
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}    
		m_pPic.SetColorTable(0,MaxColors,ColorTable);    
		delete []ColorTable;    
	}        

	for (int i = 0; i < height; i++)  
	{  
		ps = m_dstRGB.ptr<uchar>(i);  
		for (int j = 0; j < width; j++)  
		{  
			if (1 == channels)  
			{  
				*(pimg + i*step + j) = ps[j];  
			}  
			else if (3 == channels)  
			{  
				*(pimg + i*step + j*3) = ps[j*3];  
				*(pimg + i*step + j*3 + 1) = ps[j*3 + 1];  
				*(pimg + i*step + j*3 + 2) = ps[j*3 + 2];  
			}  
		}  
	}
}  

void CMYTEST2Doc::Mat16bToCImage(int maxV, int minV,Mat m_dstRGB, BOOL bWhiteZero)  
{  
	if(bChange==0)
		m_dstRGB=m_srcRGB;
	if(bChange==1)
		m_dstRGB=Dst;
	m_srcMaxValue=maxV;
	m_srcMinValue=minV;
	if (maxV == minV)
	{
		MessageBox(NULL, TEXT("需满足最大值!=最小值!"), TEXT("Open"), MB_OK);
		return;
	}

	int width = m_dstRGB.cols;
	int height = m_dstRGB.rows;  
	int channels = m_dstRGB.channels();  

	if (channels > 1)
	{
		MessageBox(NULL, TEXT("暂不支持多通道16bit图像!"), TEXT("Open"), MB_OK);
		return;
	}

	m_pPic.Destroy();//这一步是防止重复利用造成内存问题  
	m_pPic.Create(width,height,8*channels);  
		
	uchar* pimg = (uchar*)m_pPic.GetBits(); //获取CImage的像素存贮区的指针  
	int step = m_pPic.GetPitch();//每行的字节数,注意这个返回值有正有负  

	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置    
	// CImage中内置了调色板，我们要对他进行赋值：  
	if (1 == channels)  
	{  
		RGBQUAD* ColorTable;    
		int MaxColors=256;    
		//这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)    
		ColorTable = new RGBQUAD[MaxColors];    
		m_pPic.GetColorTable(0,MaxColors,ColorTable);//取得调色板指针    
		for (int i=0; i<MaxColors; i++)    
		{    
			ColorTable[i].rgbBlue = (BYTE)(bWhiteZero==FALSE ? i : (MaxColors-1-i));;      
			ColorTable[i].rgbGreen = (BYTE)(bWhiteZero==FALSE ? i : (MaxColors-1-i));;    
			ColorTable[i].rgbRed = (BYTE)(bWhiteZero==FALSE ? i : (MaxColors-1-i));;    
		}    
		m_pPic.SetColorTable(0,MaxColors,ColorTable);    
		delete []ColorTable;    
	}        

	for (int i = 0; i < height; i++)  
	{  
		ushort *ps = m_dstRGB.ptr<ushort>(i);  
		for (int j = 0; j < width; j++)  
		{  
			if (1 == channels)  
			{  
				*(pimg + i*step + j) = uchar((ps[j]-minV)*255/(maxV-minV));
			}  
			else if (3 == channels)  
			{  
				*(pimg + i*step + j*3) = uchar((ps[j*3]-minV)*255/(maxV-minV));
				*(pimg + i*step + j*3 + 1) = uchar((ps[j*3 + 1]-minV)*255/(maxV-minV));
				*(pimg + i*step + j*3 + 2) = uchar((ps[j*3 + 2]-minV)*255/(maxV-minV));
			}  
		}  
	}
}  

string CMYTEST2Doc::CString2StdString(const CString& cstr)  
{     
	CT2A str(cstr);  
	return string(str.m_psz);  
}

CString CMYTEST2Doc::GetFileExt(const CString &str)	//获取文件扩展名
{
	CString pathstr=_T(""); 
	int pos=str.ReverseFind(_T('.'));
	int start = str.ReverseFind(_T('\\'));
	if(pos!=-1&&start==-1)
	{
		pathstr=str.Right(str.GetLength()-pos-1);

	}
	else if(pos!=-1&&start!=-1)
	{
		pathstr=pos>start?str.Right(str.GetLength()-pos-1):NULL;

	}


	return pathstr;
}


void  CMYTEST2Doc::ChangeSize()
{
	CChangesize Dlg;
	
if(Dlg.DoModal()==IDOK)
		{
	 Mat m_dstRGB=m_srcRGB;
	Size GetS(Dlg.m_Width,Dlg.m_Height);
	if(Dlg.m_Width<m_dstRGB.cols&&Dlg.m_Height<m_dstRGB.rows)
	resize(m_srcRGB,m_dstRGB,GetS,CV_INTER_AREA);
	else
	resize(m_srcRGB,m_dstRGB,GetS,CV_INTER_LINEAR);
	Mat16bToCImage(m_srcMaxValue, m_srcMinValue,m_dstRGB,bWhiteZero);

	}
}

void CMYTEST2Doc::ToBig()
{    
	
	Size GetS(Dst.cols*2,Dst.rows*2);
	SizeSelect(GetS);
}
void CMYTEST2Doc::ToSmall()
{     
	Size GetS(Dst.cols/2,Dst.rows/2);
	SizeSelect(GetS);
}
void CMYTEST2Doc::SizeSelect(Size GetS)
{
	Dst=m_srcRGB;
	resize(m_srcRGB,Dst,GetS,CV_INTER_LINEAR);
	bChange=1;
	Mat16bToCImage(m_srcMaxValue, m_srcMinValue,Dst,bWhiteZero);
}


void CMYTEST2Doc::OnSrcrgb()
{
bChange=0;
Mat16bToCImage(m_srcMaxValue, m_srcMinValue,m_srcRGB,bWhiteZero);	// TODO: 在此添加命令处理程序代码
}


void CMYTEST2Doc::OnUpdateSrcrgb(CCmdUI *pCmdUI)
{

Mat16bToCImage(m_srcMaxValue, m_srcMinValue,m_srcRGB,bWhiteZero);		// TODO: 在此添加命令更新用户界面处理程序代码
}
