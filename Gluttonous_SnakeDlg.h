
// Gluttonous_SnakeDlg.h: 头文件
//

#pragma once


// CGluttonousSnakeDlg 对话框
class CGluttonousSnakeDlg : public CDialogEx
{
// 构造
public:
	CGluttonousSnakeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLUTTONOUS_SNAKE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnSetfocusStartbutton();
//	afx_msg void OnKillfocusStartbutton();
//	afx_msg void OnClickedStartbutton();
protected:
//	afx_msg LRESULT OnInitStartbutton(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool StartButtonInit();
	CBitmapButton CBbutton_start;
	// 用于绘画开始界面的蛇
	void StartSnake();
	void StartBackground();
	CBitmap* BitmapLoader(int part, int direction, BITMAP &bp);
	afx_msg void OnClickedStartbutton();
protected:
	CMenu m_Menu;
public:
//	afx_msg void OnAbout();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHelp();
	afx_msg void OnAbout();
};
