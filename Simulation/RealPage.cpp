// RealPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Simulation.h"
#include "RealPage.h"
#include "afxdialogex.h"


// CRealPage 对话框

IMPLEMENT_DYNAMIC(CRealPage, CPropertyPage)

CRealPage::CRealPage()
	: CPropertyPage(CRealPage::IDD)
{

}

CRealPage::~CRealPage()
{
}

void CRealPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



void CRealPage::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPropertyPage::OnPaint();
	}
}



BEGIN_MESSAGE_MAP(CRealPage, CPropertyPage)
END_MESSAGE_MAP()


// CRealPage 消息处理程序
