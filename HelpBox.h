#pragma once


// HelpBox 对话框

class HelpBox : public CDialog
{
	DECLARE_DYNAMIC(HelpBox)

public:
	HelpBox(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HelpBox();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELPBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
