#pragma once

#include "resource.h"
// CRealPage 对话框

class CRealPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRealPage)

public:
	CRealPage();
	virtual ~CRealPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MEDIUM };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};
