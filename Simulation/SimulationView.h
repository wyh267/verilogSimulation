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

// SimulationView.h : CSimulationView 类的接口
//

#pragma once

#define BM_GOTDATA_MSG (WM_USER + 200)

class CSimulationView : public CScrollView
{
protected: // 仅从序列化创建
	CSimulationView();
	DECLARE_DYNCREATE(CSimulationView)

// 特性
public:
	CSimulationDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	int mouse_y;
	int mouse_x;

	//鼠标左键按下时的坐标
	//CPoint left_down_point;
	int mouse_left_x;
	int mouse_left_y;
	bool left_down;


	//scroll位置
	long scroll_pos_x;
	long scroll_pos_y;

	void updatePaint(bool undo=false);

	//显示变量名
	bool b_display_name;


	//发送信息到outputWnd
	void sendMessageToOutput(int num,LPCTSTR info,bool display);

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnZoomOut();
	afx_msg void OnZoomIn();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUnDo();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnBmGotdataMsg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnButton8();
	afx_msg void OnButton12();
	afx_msg void OnDisplayX();
	afx_msg void OnDisplayY();
	afx_msg void OnDisplayVarName();
	afx_msg void OnRefuse();
};

#ifndef _DEBUG  // SimulationView.cpp 中的调试版本
inline CSimulationDoc* CSimulationView::GetDocument() const
   { return reinterpret_cast<CSimulationDoc*>(m_pDocument); }
#endif

