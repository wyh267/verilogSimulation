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

// SimulationView.cpp : CSimulationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Simulation.h"
#endif

#include "SimulationDoc.h"
#include "SimulationView.h"

#include "MainFrm.h"


#include "Data.h"

#include "AISCTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimulationView

IMPLEMENT_DYNCREATE(CSimulationView, CScrollView)

BEGIN_MESSAGE_MAP(CSimulationView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSimulationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON2, &CSimulationView::OnZoomOut)
	ON_COMMAND(ID_BUTTON3, &CSimulationView::OnZoomIn)
	ON_COMMAND(ID_BUTTON4, &CSimulationView::OnButton4)
	ON_COMMAND(ID_BUTTON5, &CSimulationView::OnButton5)
	ON_COMMAND(ID_BUTTON6, &CSimulationView::OnButton6)
	ON_COMMAND(ID_BUTTON7, &CSimulationView::OnButton7)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32777, &CSimulationView::OnUnDo)
//	ON_WM_LBUTTONDBLCLK()
ON_MESSAGE(BM_GOTDATA_MSG, &CSimulationView::OnBmGotdataMsg)
ON_COMMAND(ID_BUTTON8, &CSimulationView::OnButton8)
ON_COMMAND(ID_BUTTON12, &CSimulationView::OnButton12)
ON_COMMAND(ID_32786, &CSimulationView::OnDisplayX)
ON_COMMAND(ID_32787, &CSimulationView::OnDisplayY)
ON_COMMAND(ID_32788, &CSimulationView::OnDisplayVarName)
ON_COMMAND(ID_32790, &CSimulationView::OnRefuse)
END_MESSAGE_MAP()

// CSimulationView 构造/析构

CSimulationView::CSimulationView()
{
	// TODO: 在此处添加构造代码

}

CSimulationView::~CSimulationView()
{
}

BOOL CSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	mouse_x=0;
	mouse_y=0;
	mouse_left_x=0;
	mouse_left_y=0;
	left_down=false;
	b_display_name=false;
	return CScrollView::PreCreateWindow(cs);
}

// CSimulationView 绘制

void CSimulationView::OnDraw(CDC* pDC)
{
	CSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Data *pData=Data::shareData();
	int left,right,top,bottom;
	CRect rect;
	GetClientRect(&rect);
	
	left=rect.left+GetScrollPos(SB_HORZ);
	right=rect.right+GetScrollPos(SB_HORZ);
	top=rect.top+GetScrollPos(SB_VERT);
	bottom=rect.bottom+GetScrollPos(SB_VERT);
	
	CRect rect2;
	rect2.SetRect(left,top,right,bottom);

	for(int i=0;i<pData->data_num;i++)
	{
		pDC->SetTextColor(RGB(255,0,0));
		CPen* pPen ; //创建一支新的笔
		pPen=new CPen ;
		pPen->CreatePen(PS_SOLID,1,pData->pData_info[i].color) ;
		pDC->SelectObject(pPen) ;
		bool b_name=false;
		for(int j=0;j<MAX_DATA_NUM;j++)
		{
			
			int x,y,x1,y1,data;
			bool res;
			
			res=pData->getPointFromIndex(i,j,&x1,&y1,&x,&y,&data);
			if(rect2.PtInRect(CPoint(x,y)) || rect2.PtInRect(CPoint(x1,y1)))
			{
				
				pDC->MoveTo(x1,y1);
				pDC->LineTo(x,y1);
				pDC->LineTo(x,y);
				if(res==true)
				{
					CString str;
					str.Format(_T("%d"),data);
					
					pDC->TextOutW(x+5,y-20,str);
				}

				if(b_name==false && b_display_name ==true)
				{
					
					b_name=true;
					pDC->TextOutW(x+5,y-20,pData->pData_info[i].node_name);
				}
				
			}
		}
		pPen->DeleteObject();
		delete pPen;
		pData->drawXY(i,pDC,rect2);
		
	}

	// TODO: 在此处为本机数据添加绘制代码
}

void CSimulationView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CRect rect;
	GetClientRect(&rect);
	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = rect.right;
	sizeTotal.cy = rect.bottom;
	SetScrollSizes(MM_TEXT, sizeTotal);
	scroll_pos_x=0;
	scroll_pos_y=0;
	SetScrollPos(SB_VERT,scroll_pos_y);
	SetScrollPos(SB_HORZ,scroll_pos_x);
	//printf("cx:%d,cy:%d,x:%d,y%d\n",sizeTotal.cx,sizeTotal.cx,scroll_pos_x,scroll_pos_y);
}


// CSimulationView 打印


void CSimulationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSimulationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSimulationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


//重绘函数
void CSimulationView::updatePaint(bool undo)
{
	if(undo==false)
	{
	SCROLLINFO sizeTotal_old_y;
	SCROLLINFO sizeTotal_old_x;
	
	GetScrollInfo(SB_VERT,&sizeTotal_old_y);
	GetScrollInfo(SB_HORZ,&sizeTotal_old_x);
	scroll_pos_y=sizeTotal_old_y.nPos;
	scroll_pos_x=sizeTotal_old_x.nPos;
	float posX=((float)scroll_pos_x/sizeTotal_old_x.nMax);
	float posY=((float)scroll_pos_y/sizeTotal_old_y.nMax);
	
	CSize sizeTotal;	
	Data *pData=Data::shareData();
	pData->getScrollRange(&sizeTotal.cx,&sizeTotal.cy);
	SetScrollSizes(MM_TEXT, sizeTotal);

	SetScrollPos(SB_VERT,(int)(sizeTotal.cy*posY));
	SetScrollPos(SB_HORZ,(int)(sizeTotal.cx*posX));


	}else
	{
		CSize sizeTotal;	
		Data *pData=Data::shareData();
		pData->getScrollRange(&sizeTotal.cx,&sizeTotal.cy);
		SetScrollSizes(MM_TEXT, sizeTotal);

		SetScrollPos(SB_VERT,scroll_pos_y);
		SetScrollPos(SB_HORZ,scroll_pos_x);
	}

	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);
}



// CSimulationView 诊断

#ifdef _DEBUG
void CSimulationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSimulationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}






CSimulationDoc* CSimulationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimulationDoc)));
	return (CSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimulationView 消息处理程序

//Y放大
void CSimulationView::OnZoomOut()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();
	
	

	pData->scanlingYplus();

	//Invalidate();
	updatePaint();

}

//Y缩小
void CSimulationView::OnZoomIn()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();

	pData->scanlingYsub();

	//Invalidate();
	updatePaint();
}

//X放大
void CSimulationView::OnButton4()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();

	pData->scanlingXplus();
;
	//Invalidate();
	updatePaint();
}

//X缩小
void CSimulationView::OnButton5()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();

	pData->scanlingXsub();

	//Invalidate();
	updatePaint();

}

//整体放大
void CSimulationView::OnButton6()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();

	pData->scanlingXplus();
	pData->scanlingYplus();


	updatePaint();
}


//整体缩小
void CSimulationView::OnButton7()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();

	pData->scanlingXsub();
	pData->scanlingYsub();

	//Invalidate();
	updatePaint();

}



//鼠标移动
void CSimulationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CDC *pDC=GetDC();
	CRect rect;
	GetClientRect(&rect); 

	int nDrawmode = pDC->SetROP2(R2_NOT);
	if(rect.PtInRect(point) && left_down==true)
	{
		
		
		
		pDC->MoveTo(0,mouse_y);
		pDC->LineTo(5000,mouse_y);

		pDC->MoveTo(mouse_x,0);
		pDC->LineTo(mouse_x,8000);
		
		pDC->MoveTo(0,point.y);
		pDC->LineTo(5000,point.y);

		pDC->MoveTo(point.x,0);
		pDC->LineTo(point.x,8000);


		mouse_x=point.x;
		mouse_y=point.y;
		CString str;
		str.Format(_T("移动坐标: X:%ld Y:%ld"),point.x,point.y);
		sendMessageToOutput(1,str,false);
		
		
	}
	
	pDC->SetROP2(nDrawmode);
	ReleaseDC(pDC);
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CSimulationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC=GetDC();
	CRect rect;
	GetClientRect(&rect); 
	if(rect.PtInRect(point))
	{
		
		
		
		pDC->MoveTo(0,point.y);
		pDC->LineTo(5000,point.y);

		pDC->MoveTo(point.x,0);
		pDC->LineTo(point.x,8000);

		mouse_left_x=point.x;
		mouse_left_y=point.y;
		
		left_down=true;
		CString str;
		str.Format(_T("起始坐标: X:%ld Y:%ld"),point.x,point.y);
		sendMessageToOutput(1,str,true);

		sendMessageToOutput(1,_T(" "),true);
	}
	
	ReleaseDC(pDC);
	CScrollView::OnLButtonDown(nFlags, point);
	
	//COutputList* prt =RUNTIME_CLASS(COutputList);
	
	
}


void CSimulationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//printf("X:%d,Y:%d\n",point.x,point.y);
	CDC *pDC=GetDC();
	left_down=false;
	if(abs(point.x-mouse_left_x)>10)
	{
		int scal_x=abs(point.x-mouse_left_x);
		int scal_y=abs(point.y-mouse_left_y);
		
		
		float left,top;
		CRect rect;
		GetClientRect(&rect); 


		Data *pData=Data::shareData();
		pData->scalingXY((float)rect.right/scal_x,(float)rect.bottom/scal_y);

		int nDrawmode = pDC->SetROP2(R2_NOT);
		if(rect.PtInRect(point))
		{
		
		
		
			pDC->MoveTo(0,mouse_left_y);
			pDC->LineTo(5000,mouse_left_y);

			pDC->MoveTo(mouse_left_x,0);
			pDC->LineTo(mouse_left_x,8000);
		

			pDC->MoveTo(0,mouse_y);
			pDC->LineTo(5000,mouse_y);

			pDC->MoveTo(mouse_x,0);
			pDC->LineTo(mouse_x,8000);

		
			mouse_x=0;
			mouse_y=0;
			CString str;
			str.Format(_T("截至坐标: X:%ld Y:%ld"),point.x,point.y);
			sendMessageToOutput(1,str,false);
			sendMessageToOutput(1,_T(" "),true);
		
		}
	
		pDC->SetROP2(nDrawmode);
		ReleaseDC(pDC);
		CScrollView::OnLButtonUp(nFlags, point);

	
		left=(float)(rect.left+GetScrollPos(SB_HORZ)+mouse_left_x);
		top=(float)(rect.top+GetScrollPos(SB_VERT)+mouse_left_y);
	
		SCROLLINFO si_v;
		GetScrollInfo(SB_VERT,&si_v);

		SCROLLINFO si_h;
		GetScrollInfo(SB_HORZ,&si_h);

		scroll_pos_x=si_h.nPos;
		scroll_pos_y=si_v.nPos;


		left=left/si_h.nMax;
		top=top/si_v.nMax;
		CSize sizeTotal;	
		pData->getScrollRange(&sizeTotal.cx,&sizeTotal.cy);
		SetScrollSizes(MM_TEXT, sizeTotal);
		SetScrollPos(SB_VERT,(int)(top*sizeTotal.cy));
		SetScrollPos(SB_HORZ,(int)(left*sizeTotal.cx));

		mouse_left_x=0;
		mouse_left_y=0;
		
		
		InvalidateRect(rect);
		//updatePaint();
	}else
	{
		int nDrawmode = pDC->SetROP2(R2_NOT);
		pDC->MoveTo(0,mouse_left_y);
		pDC->LineTo(5000,mouse_left_y);

		pDC->MoveTo(mouse_left_x,0);
		pDC->LineTo(mouse_left_x,8000);
		

		pDC->MoveTo(0,mouse_y);
		pDC->LineTo(5000,mouse_y);

		pDC->MoveTo(mouse_x,0);
		pDC->LineTo(mouse_x,8000);

		
		mouse_x=0;
		mouse_y=0;
		mouse_left_x=0;
		mouse_left_y=0;
		pDC->SetROP2(nDrawmode);
		ReleaseDC(pDC);
	}
}



//撤销
void CSimulationView::OnUnDo()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();
	pData->scalingUndo();
	
	updatePaint(true);
	sendMessageToOutput(1,_T("撤销操作..."),true);

}


void CSimulationView::sendMessageToOutput(int num,LPCTSTR info,bool display)
{
	CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->sendInformation(num,info,display);
}


//void CSimulationView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CScrollView::OnLButtonDblClk(nFlags, point);
//}


afx_msg LRESULT CSimulationView::OnBmGotdataMsg(WPARAM wParam, LPARAM lParam)
{
	updatePaint(true);
	return 0;
}


//启动应用程序
void CSimulationView::OnButton8()
{
	// TODO: 在此添加命令处理程序代码
	AISCTest();

}


void CSimulationView::OnButton12()
{
	// TODO: 在此添加命令处理程序代码
	AISCTestStop();
}


void CSimulationView::OnDisplayX()
{
	// TODO: 在此添加命令处理程序代码// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();
	pData->EnableX();
	updatePaint();
	
}


void CSimulationView::OnDisplayY()
{
	// TODO: 在此添加命令处理程序代码
	Data *pData=Data::shareData();
	pData->EnableY();
	updatePaint();
}


void CSimulationView::OnDisplayVarName()
{
	// TODO: 在此添加命令处理程序代码
	if(b_display_name)
		b_display_name=false;
	else
		b_display_name=true;

	updatePaint();
}


void CSimulationView::OnRefuse()
{
	// TODO: 在此添加命令处理程序代码
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);
}
