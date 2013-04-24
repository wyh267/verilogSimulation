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

#include "stdafx.h"
#include "ViewTree.h"

#include "Data.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	g_fDragging=FALSE;
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CViewTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//CTreeCtrl* pTreeCtrl = this;
 //CPoint ptCurSel(0,0);
 //TVHITTESTINFO HitTestInfo;
 //// 通过鼠标在客户区中的位置
 //GetCursorPos(&ptCurSel);
 //pTreeCtrl->ScreenToClient(&ptCurSel);  
 //// 获取当前选择的是哪一项
 //HitTestInfo.pt = ptCurSel;  
 //HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);
 //
 //if(hSelect != NULL)
 //{
 // CString strItem = pTreeCtrl->GetItemText(hSelect);
 // ::AfxMessageBox( strItem);
 //}
 //// 设置该项为选中状态
 //pTreeCtrl->SelectItem(hSelect);
  
 //以下方法获取的是上一次处于选中状态的项首先将点击的对象选中
 //CTreeCtrl* pTreeCtrl = this;
 //HTREEITEM hSelect = pTreeCtrl->GetSelectedItem();
 //HTREEITEM hLight = pTreeCtrl->GetDropHilightItem();
 //if((hLight != NULL) && (hSelect != hLight))
 // hSelect = hLight;
 //if(hSelect   ==   NULL)
 // return;
 //pTreeCtrl->SelectItem(hSelect);
 //
 ////pTreeCtrl->GetIndent();
 //printf("hSelect:%d\n",hSelect);
 ////编辑当前选中对象名称
 //pTreeCtrl->EditLabel(hSelect);
 //if( NULL != hSelect )
 //{
 // CString strItem = pTreeCtrl->GetItemText(hSelect);
 // /*if(strItem == _T("控制器"));
 // {
 //  pTreeCtrl->SetItemText(hSelect, _T("改变后的控制器"));
 // }*/
 // ::AfxMessageBox( strItem); 
 //}
 
 *pResult = 0;
	
}


void CViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	//如果是无意拖动，则放弃操作
	if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )
		return;

	m_hItemDragS = pNMTreeView->itemNew.hItem;
	m_hItemDragD = NULL;

	//得到用于拖动时显示的图象列表
	m_pDragImage = CreateDragImage( m_hItemDragS );
	if( !m_pDragImage )
		return;

	m_bDragging = true;
	m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
	CPoint  pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter ( this,pt );  //"this"将拖动操作限制在该窗口
	SetCapture();

	m_nScrollTimerID = SetTimer( 2,40,NULL );
}


void CViewTree::Main_OnBeginDrag(HWND hwndTV, LPNMTREEVIEW lpnmtv) 
{ 
    
    return;
}

void CViewTree::Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    
    return; 
}

void CViewTree::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM  hItem;
	UINT       flags;

	//检测鼠标敏感定时器是否存在,如果存在则删除,删除后再定时
	if( m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
	}
	m_nHoverTimerID = SetTimer( 1,800,NULL );  //定时为 0.8 秒则自动展开
	m_HoverPoint = point;

	if( m_bDragging )
	{
		CPoint  pt = point;
		CImageList::DragMove( pt );

		//鼠标经过时高亮显示
		CImageList::DragShowNolock( false );  //避免鼠标经过时留下难看的痕迹
		if( (hItem = HitTest(point,&flags)) != NULL )
		{
			SelectDropTarget( hItem );
			m_hItemDragD = hItem;
		}
		CImageList::DragShowNolock( true );

		//当条目被拖曳到左边缘时，将条目放在根下
		CRect  rect;
		GetClientRect( &rect );
		if( point.x < rect.left + 20 )
			m_hItemDragD = NULL;
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}


void CViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if( m_bDragging )
	{
		m_bDragging = FALSE;
		CImageList::DragLeave( this );
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;

		SelectDropTarget( NULL );
		
		if( m_hItemDragS == m_hItemDragD )
		{
			KillTimer( m_nScrollTimerID );
			return;
		}

		Expand( m_hItemDragD,TVE_EXPAND );
		HTREEITEM  htiParent = m_hItemDragD;
		htiParent = GetParentItem(htiParent);

		/*MessageBox(GetItemText(m_hItemDragD));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));*/
		////如果是由父节点拖向子节点
		//while( (htiParent = GetParentItem(htiParent)) != NULL )
		//{
		//	if( htiParent == m_hItemDragS )
		//	{
		//		//建立一个临时节点以完成操作
		//		HTREEITEM  htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST );
		//		HTREEITEM  htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
		//		DeleteItem( htiNewTemp );
		//		SelectItem( htiNew );
		//		KillTimer( m_nScrollTimerID );
		//		return;
		//	}
		//}

		HTREEITEM  htiNew = CopyBranch( m_hItemDragS,htiParent,m_hItemDragD );
		HTREEITEM  oldNew = CopyBranch( m_hItemDragD,htiParent,m_hItemDragS );
		
		Data *pDate=Data::shareData();
		int tmp=pDate->pData_info[_ttoi(GetItemText(GetChildItem(htiNew)))].node_sort;
		pDate->pData_info[_ttoi(GetItemText(GetChildItem(htiNew)))].node_sort=pDate->pData_info[_ttoi(GetItemText(GetChildItem(oldNew)))].node_sort;
		pDate->pData_info[_ttoi(GetItemText(GetChildItem(oldNew)))].node_sort=tmp;

		//AfxGetMainWnd()->GetActiveView()->SendMessage()
		CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
		pFrame->GetActiveView()->SendMessage(BM_GOTDATA_MSG);
		DeleteItem( m_hItemDragS );
		DeleteItem( m_hItemDragD );
		SelectItem( htiNew );
		KillTimer( m_nScrollTimerID );
	}
	CTreeCtrl::OnLButtonUp(nFlags, point);
}



//拷贝条目
HTREEITEM CViewTree::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT  tvstruct;
	HTREEITEM        hNewItem;
	CString          sText;

	//得到源条目的信息
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask  = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText    = sText.LockBuffer ();

	//将条目插入到合适的位置
	tvstruct.hParent         = htiNewParent;
	tvstruct.hInsertAfter    = htiAfter;
	tvstruct.item.mask       = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	//限制拷贝条目数据和条目状态
	SetItemData( hNewItem,GetItemData(hItem) );
	SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	return hNewItem;
}

//拷贝分支
HTREEITEM CViewTree::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	HTREEITEM  hChild;
	HTREEITEM  hNewItem = CopyItem( htiBranch,htiNewParent,htiAfter );
	hChild = GetChildItem( htiBranch );
	
	//printf("%s",GetItemText(hChild));
	while( hChild != NULL )
	{
		CopyBranch( hChild,hNewItem,htiAfter );
		hChild = GetNextSiblingItem( hChild );
		
	}

	return  hNewItem;
}

