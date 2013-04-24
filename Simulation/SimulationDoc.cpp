// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// SimulationDoc.cpp : CSimulationDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Simulation.h"
#endif

#include "SimulationDoc.h"

#include "MainFrm.h"
#define BM_GOTDATA_MSG (WM_USER + 200)

#include "Data.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSimulationDoc

IMPLEMENT_DYNCREATE(CSimulationDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimulationDoc, CDocument)
	ON_COMMAND(ID_BUTTON10, &CSimulationDoc::OnButton10)
	ON_COMMAND(ID_BUTTON13, &CSimulationDoc::OnReadNext)
END_MESSAGE_MAP()


// CSimulationDoc 构造/析构

CSimulationDoc::CSimulationDoc()
{
	// TODO: 在此添加一次性构造代码

}

CSimulationDoc::~CSimulationDoc()
{
}

BOOL CSimulationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSimulationDoc 序列化

void CSimulationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
		pData=Data::shareData(_T("d:\\a.dat"));
		pData->configureData(20);
		pData->ReadFile();
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSimulationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSimulationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSimulationDoc::SetSearchContent(const CString& value)
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

// CSimulationDoc 诊断

#ifdef _DEBUG
void CSimulationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimulationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSimulationDoc 命令


void CSimulationDoc::OnButton10()
{
	// TODO: 在此添加命令处理程序代码
	pData=Data::shareData();
	//pData->configureData(20);
	pData->ReadNextFile(Data::kStart);
	CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->SendMessage(BM_DATA_RECIVE,0x9001,0);
	pFrame->GetActiveView()->SendMessage(BM_GOTDATA_MSG);
}


void CSimulationDoc::OnReadNext()
{
	// TODO: 在此添加命令处理程序代码
	pData=Data::shareData();
	//pData->configureData(20);
	pData->ReadNextFile(Data::kNext);
	CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->GetActiveView()->SendMessage(BM_GOTDATA_MSG);
}
